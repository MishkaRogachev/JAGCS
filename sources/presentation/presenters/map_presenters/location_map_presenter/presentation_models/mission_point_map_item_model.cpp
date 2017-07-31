#include "mission_point_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission_item.h"

using namespace presentation;

MissionPointMapItemModel::MissionPointMapItemModel(domain::MissionService* service,
                                                   QObject* parent):
    QAbstractListModel(parent),
    m_service(service)
{
    connect(service, &domain::MissionService::missionItemAdded,
            this, &MissionPointMapItemModel::onMissionItemAdded);
    connect(service, &domain::MissionService::missionItemRemoved,
            this, &MissionPointMapItemModel::onMissionItemRemoved);
    connect(service, &domain::MissionService::missionItemChanged,
            this, &MissionPointMapItemModel::onMissionItemChanged);

    for (const dao::MissionItemPtr& item: service->missionItems())
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

    const dao::MissionItemPtr& item = m_items.at(index.row());

    switch (role)
    {
    case ItemCoordinateRole:
    {
        if (item->command() == dao::MissionItem::Waypoint ||
            item->command() == dao::MissionItem::Takeoff ||
            item->command() == dao::MissionItem::Landing ||
            item->command() == dao::MissionItem::LoiterAltitude ||
            item->command() == dao::MissionItem::LoiterTurns)
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
        if (item->command() == dao::MissionItem::Takeoff)
            return "qrc:/icons/takeoff.svg";
        else if (item->command() == dao::MissionItem::Landing)
            return "qrc:/icons/landing.svg";
        return QString("");
    case ItemAcceptanceRadius:
    {
        if (item->command() == dao::MissionItem::Waypoint)
            return item->radius();
        else return 0;
    }
    case ItemRadius:
    {
        if (item->command() == dao::MissionItem::LoiterAltitude ||
            item->command() == dao::MissionItem::LoiterTurns)
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
        const dao::MissionItemPtr& item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_items.append(item);
    this->endInsertRows();
}

void MissionPointMapItemModel::onMissionItemRemoved(
        const dao::MissionItemPtr& item)
{
    int row = m_items.indexOf(item);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);
    this->endRemoveRows();

    emit dataChanged(this->index(row),
                     this->index(m_items.count() - 1), { ItemSequenceRole });
}

void MissionPointMapItemModel::onMissionItemChanged(
        const dao::MissionItemPtr& item)
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
        const dao::MissionItemPtr& item) const
{
    return this->index(m_items.indexOf(item));
}
