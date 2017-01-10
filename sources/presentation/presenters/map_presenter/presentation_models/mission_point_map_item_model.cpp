#include "mission_point_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "position_mission_item.h"

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
            return QVariant::fromValue(QGeoCoordinate(positionItem->latitude(),
                                                      positionItem->longitude()));
        else
            return QVariant::fromValue(QGeoCoordinate());
    }
    case ItemSequenceRole:
        return QVariant::fromValue(item->sequence());
    case ItemIconRole:
        if (item->command() == domain::MissionItem::Home)
            return "qrc:/icons/home.svg";
        if (item->command() == domain::MissionItem::Takeoff)
            return "qrc:/icons/takeoff.svg";
        if (item->command() == domain::MissionItem::Landing)
            return "qrc:/icons/landing.svg";
        return QString("");
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
    }

    this->endInsertRows();
}

void MissionPointMapItemModel::removeMissionItem(domain::MissionItem* item)
{
    int row = m_items.indexOf(item);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);

    this->endRemoveRows();

    emit dataChanged(this->index(row), this->index(m_items.count() - 1),
    { ItemSequenceRole });
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
