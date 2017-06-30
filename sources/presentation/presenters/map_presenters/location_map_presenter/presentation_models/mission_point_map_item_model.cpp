#include "mission_point_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "mission_item.h"

using namespace presentation;

MissionPointMapItemModel::MissionPointMapItemModel(db::DbFacade* dbFacade, QObject* parent):
    QAbstractListModel(parent),
    m_dbFacade(dbFacade)
{
    connect(dbFacade, &db::DbFacade::missionItemAdded,
            this, &MissionPointMapItemModel::onMissionItemAdded);
    connect(dbFacade, &db::DbFacade::missionItemRemoved,
            this, &MissionPointMapItemModel::onMissionItemRemoved);
    connect(dbFacade, &db::DbFacade::missionItemChanged,
            this, &MissionPointMapItemModel::onMissionItemChanged);

    for (const db::MissionItemPtr& item: dbFacade->missionItems())
    {
        this->onMissionItemAdded(item);
    }
}

int MissionPointMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant MissionPointMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) return QVariant();

    const db::MissionItemPtr& item = m_items.at(index.row());

    switch (role)
    {
    case ItemCoordinateRole:
    {
        if (item->command() == db::MissionItem::Waypoint ||
            item->command() == db::MissionItem::Landing ||
            item->command() == db::MissionItem::LoiterAltitude ||
            item->command() == db::MissionItem::LoiterTurns)
        {
            QGeoCoordinate coordinate(item->latitude(), item->longitude());
            if (coordinate.isValid()) return QVariant::fromValue(coordinate);
            return QVariant::fromValue(QGeoCoordinate());
        }
        else return QVariant::fromValue(QGeoCoordinate());
    }
    case ItemSequenceRole:
        return QVariant::fromValue(item->sequence());
    case ItemIconRole:
        if (item->command() == db::MissionItem::Landing)
            return "qrc:/icons/landing.svg";
        return QString("");
    case ItemAcceptanceRadius:
    {
        if (item->command() == db::MissionItem::Waypoint)
            return item->radius();
        else return 0;
    }
    case ItemRadius:
    {
        if (item->command() == db::MissionItem::LoiterAltitude ||
            item->command() == db::MissionItem::LoiterTurns)
            return item->radius();
        else return 0;
    }
    case ItemReached:
        return item->isReached();
    default:
        return QVariant();
    }
}

void MissionPointMapItemModel::onMissionItemAdded(
        const db::MissionItemPtr& item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_items.append(item);
    this->endInsertRows();
}

void MissionPointMapItemModel::onMissionItemRemoved(
        const db::MissionItemPtr& item)
{
    int row = m_items.indexOf(item);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);
    this->endRemoveRows();

    emit dataChanged(this->index(row),
                     this->index(m_items.count() - 1), { ItemSequenceRole });
}

void MissionPointMapItemModel::onMissionItemChanged(
        const db::MissionItemPtr& item)
{
    QModelIndex index = this->itemIndex(item);
    if (!index.isValid()) return;
    emit dataChanged(index, index);
}

QHash<int, QByteArray> MissionPointMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ItemCoordinateRole] = "itemCoordinate";
    roles[ItemSequenceRole] = "itemSeq";
    roles[ItemIconRole] = "itemIcon";
    roles[ItemAcceptanceRadius] = "itemAcceptanceRadius";
    roles[ItemRadius] = "itemRadius";
    roles[ItemReached] = "itemReached";

    return roles;
}

QModelIndex MissionPointMapItemModel::itemIndex(
        const db::MissionItemPtr& item) const
{
    return this->index(m_items.indexOf(item));
}
