#include "mission_point_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

MissionPointMapItemModel::MissionPointMapItemModel(domain::MissionService* service, QObject* parent):
    QAbstractListModel(parent),
    m_service(service)
{
    connect(service, &domain::MissionService::missionItemAdded,
            this, &MissionPointMapItemModel::onMissionItemAdded);
    connect(service, &domain::MissionService::missionItemRemoved,
            this, &MissionPointMapItemModel::onMissionItemRemoved);
    connect(service, &domain::MissionService::missionItemChanged,
            this, &MissionPointMapItemModel::onMissionItemChanged);
    connect(service, &domain::MissionService::missionChanged,
            this, &MissionPointMapItemModel::onMissionChanged);

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
    const dao::MissionPtr& mission = m_service->mission(item->missionId());

    switch (role)
    {
    case ItemCoordinateRole:
    {
        if (mission->isVisible() &&
            (item->command() == dao::MissionItem::Home ||
             item->command() == dao::MissionItem::Waypoint ||
             item->command() == dao::MissionItem::Takeoff ||
             item->command() == dao::MissionItem::Landing ||
             item->command() == dao::MissionItem::LoiterUnlim ||
             item->command() == dao::MissionItem::LoiterAltitude ||
             item->command() == dao::MissionItem::LoiterTurns ||
             item->command() == dao::MissionItem::LoiterTime))
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
        if (item->command() == dao::MissionItem::Home)
            return "qrc:/icons/home.svg";
        else if (item->command() == dao::MissionItem::Takeoff)
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
        if (item->command() == dao::MissionItem::LoiterUnlim ||
            item->command() == dao::MissionItem::LoiterAltitude ||
            item->command() == dao::MissionItem::LoiterTurns ||
            item->command() == dao::MissionItem::LoiterTime)
            return item->radius();
        else return 0;
    }
    case ItemReached:
        return item->isReached();
    case ItemCurrent:
        return m_service->isItemCurrent(item);
    case ItemSelected:
        return item == m_selectedItem;
    default:
        return QVariant();
    }
}

void MissionPointMapItemModel::onMissionItemAdded(const dao::MissionItemPtr& item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_items.append(item);
    this->endInsertRows();
}

void MissionPointMapItemModel::onMissionItemRemoved(const dao::MissionItemPtr& item)
{
    int row = m_items.indexOf(item);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);
    this->endRemoveRows();

    emit dataChanged(this->index(row), this->index(m_items.count() - 1), { ItemSequenceRole });
}

void MissionPointMapItemModel::onMissionItemChanged(
        const dao::MissionItemPtr& item)
{
    QModelIndex index = this->itemIndex(item);
    if (!index.isValid()) return;
    emit dataChanged(index, index);
}

void MissionPointMapItemModel::onMissionChanged(const dao::MissionPtr& mission)
{
    for (const dao::MissionItemPtr& item: m_items)
    {
        if (item->missionId() != mission->id()) continue;

        QModelIndex index = this->itemIndex(item);
        if (index.isValid()) emit dataChanged(index, index);
    }
}

void MissionPointMapItemModel::setSelectedItem(const dao::MissionItemPtr& item)
{
    if (m_selectedItem == item) return;

    dao::MissionItemPtr oldItem = m_selectedItem;
    m_selectedItem = item;

    if (oldItem)
    {
        QModelIndex index = this->itemIndex(oldItem);
        if (index.isValid()) emit dataChanged(index, index, { ItemSelected });
    }

    if (item)
    {
        QModelIndex index = this->itemIndex(item);
        if (index.isValid()) emit dataChanged(index, index, { ItemSelected });
    }
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
    roles[ItemCurrent] = "itemCurrent";
    roles[ItemSelected] = "itemSelected";

    return roles;
}

QModelIndex MissionPointMapItemModel::itemIndex(const dao::MissionItemPtr& item) const
{
    return this->index(m_items.indexOf(item));
}
