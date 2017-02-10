#include "mission_point_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QApplication>
#include <QDebug>

// Internal
#include "waypoint_mission_item.h"
#include "loiter_mission_item.h"

using namespace presentation;

MissionPointMapItemModel::MissionPointMapItemModel(QObject* parent):
    QAbstractListModel(parent)
{}

int MissionPointMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant MissionPointMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) return QVariant();

    domain::MissionItem* item = m_items.at(index.row());

    switch (role)
    {
    case ItemCoordinateRole:
    {
        domain::PositionMissionItem* positionItem =
                qobject_cast<domain::PositionMissionItem*>(item);
        if (positionItem)
        {
            QGeoCoordinate coordinate(positionItem->latitude(),
                                      positionItem->longitude());
            if (coordinate.isValid())
            {
                return QVariant::fromValue(coordinate);
            }
        }
        return QVariant::fromValue(QGeoCoordinate());
    }
    case ItemSequenceRole:
        return QVariant::fromValue(item->sequence());
    case ItemIconRole:
        if (item->command() == domain::Command::Home)
            return "qrc:/icons/home.svg";
        if (item->command() == domain::Command::Takeoff)
            return "qrc:/icons/takeoff.svg";
        if (item->command() == domain::Command::Landing)
            return "qrc:/icons/landing.svg";
        return QString("");
    case ItemAcceptanceRadius:
    {
        domain::WaypointMissionItem* waypointItem =
                qobject_cast<domain::WaypointMissionItem*>(item);
        if (waypointItem) return waypointItem->acceptanceRadius();
        else return 0;
    }
    case ItemRadius:
    {
        domain::LoiterMissionItem* loiterItem =
                qobject_cast<domain::LoiterMissionItem*>(item);
        if (loiterItem) return loiterItem->radius();
        else return 0;
    }
    default:
        return QVariant();
    }
}

void MissionPointMapItemModel::addMissionItem(domain::MissionItem* item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());

    m_items.append(item);

    domain::PositionMissionItem* positionItem =
            qobject_cast<domain::PositionMissionItem*>(item);
    if (positionItem)
    {
        connect(positionItem, &domain::PositionMissionItem::latitudeChanged,
                this, &MissionPointMapItemModel::onCoordinateChanged);
        connect(positionItem, &domain::PositionMissionItem::longitudeChanged,
                this, &MissionPointMapItemModel::onCoordinateChanged);

        domain::WaypointMissionItem* waypointItem =
                qobject_cast<domain::WaypointMissionItem*>(positionItem);
        if (waypointItem)
        {
            connect(waypointItem,
                    &domain::WaypointMissionItem::acceptanceRadiusChanged,
                    this, &MissionPointMapItemModel::onAcceptanceRadiusChanged);
        }

        domain::LoiterMissionItem* loiterItem =
                qobject_cast<domain::LoiterMissionItem*>(positionItem);
        if (loiterItem)
        {
            connect(loiterItem, &domain::LoiterMissionItem::radiusChanged,
                    this, &MissionPointMapItemModel::onRadiusChanged);
        }
    }

    this->endInsertRows();
}

void MissionPointMapItemModel::removeMissionItem(domain::MissionItem* item)
{
    int row = m_items.indexOf(item);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);
    disconnect(item, nullptr, this, nullptr);

    this->endRemoveRows();

    emit dataChanged(this->index(row),
                     this->index(m_items.count() - 1), { ItemSequenceRole });
}

void MissionPointMapItemModel::setMissionItems(const QList<domain::MissionItem*>& items)
{
    if (!m_items.empty())
    {
        this->clearMissionItems();
    }

    for (domain::MissionItem* item: items)
    {
        if (item) this->addMissionItem(item);
    }
    emit dataChanged(this->index(0), this->index(items.count() -1));
    qApp->processEvents(); //force QtLocation to redraw
}

void MissionPointMapItemModel::clearMissionItems()
{
    this->beginRemoveRows(QModelIndex(), 0, this->rowCount() - 1);
    m_items.clear();

    this->endRemoveRows();
}

QHash<int, QByteArray> MissionPointMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ItemCoordinateRole] = "itemCoordinate";
    roles[ItemSequenceRole] = "itemSeq";
    roles[ItemIconRole] = "itemIcon";
    roles[ItemAcceptanceRadius] = "itemAcceptanceRadius";
    roles[ItemRadius] = "itemRadius";

    return roles;
}

QModelIndex MissionPointMapItemModel::missionItemIndex(
        domain::MissionItem* item) const
{
    return this->index(m_items.indexOf(item));
}

void MissionPointMapItemModel::onCommandChanged()
{
    QModelIndex index = this->missionItemIndex(
                            qobject_cast<domain::MissionItem*>(this->sender()));
    if (index.isValid()) emit dataChanged(index, index,
    { ItemCoordinateRole, // some commands not display on map
      ItemSequenceRole });
}

void MissionPointMapItemModel::onCoordinateChanged()
{
    QModelIndex index = this->missionItemIndex(
                            qobject_cast<domain::MissionItem*>(this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { ItemCoordinateRole });
}

void MissionPointMapItemModel::onAcceptanceRadiusChanged()
{
    QModelIndex index = this->missionItemIndex(
                            qobject_cast<domain::MissionItem*>(this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { ItemAcceptanceRadius });
}

void MissionPointMapItemModel::onRadiusChanged()
{
    QModelIndex index = this->missionItemIndex(
                            qobject_cast<domain::MissionItem*>(this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { ItemRadius });
}
