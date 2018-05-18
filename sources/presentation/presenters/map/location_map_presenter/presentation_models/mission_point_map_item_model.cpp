#include "mission_point_map_item_model.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"

#include "mission_item.h"
#include "mission_service.h"

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
    connect(service, &domain::MissionService::currentItemChanged,
            this, &MissionPointMapItemModel::onCurrentItemChanged);
    connect(service, &domain::MissionService::missionChanged,
            this, &MissionPointMapItemModel::onMissionChanged);

    for (const dto::MissionItemPtr& item: service->missionItems())
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

    const dto::MissionItemPtr& item = m_items.at(index.row());
    if (item.isNull()) return QVariant();

    switch (role)
    {
    case ItemRole:
        return QVariant::fromValue(*item.data());
    case ItemCoordinateRole:
    {
        if (item->isPositionatedItem())
        {
            if (item->coordinate().isValid()) return QVariant::fromValue(item->coordinate());
        }
        return QVariant::fromValue(QGeoCoordinate());
    }
    case ItemVisibleRole:
    {
        return settings::Provider::value(settings::mission::mission +
                                         QString::number(item->missionId()) + "/" +
                                         settings::visibility).toBool()
                && (item->isPositionatedItem());
    }
    case ItemAcceptanceRadius:
    {
        if (item->command() == dto::MissionItem::Waypoint)
            return item->parameter(dto::MissionItem::Radius, 0);
        else return 0;
    }
    case ItemRadius:
    {
        if (item->command() == dto::MissionItem::LoiterUnlim ||
            item->command() == dto::MissionItem::LoiterAltitude ||
            item->command() == dto::MissionItem::LoiterTurns ||
            item->command() == dto::MissionItem::LoiterTime)
            return item->parameter(dto::MissionItem::Radius, 0);
        else return 0;
    }
    case ItemIndex:
        return index.row();
    case ItemCurrent:
        return m_service->isCurrentForVehicle(item) > 0;
    default:
        return QVariant();
    }
}

void MissionPointMapItemModel::onMissionItemAdded(const dto::MissionItemPtr& item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_items.append(item);
    this->endInsertRows();
}

void MissionPointMapItemModel::onMissionItemRemoved(const dto::MissionItemPtr& item)
{
    int row = m_items.indexOf(item);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);
    this->endRemoveRows();

    emit dataChanged(this->index(row), this->index(m_items.count() - 1), { ItemRole });
}

void MissionPointMapItemModel::onMissionItemChanged(const dto::MissionItemPtr& item)
{
    QModelIndex index = this->itemIndex(item);
    if (!index.isValid()) return;
    emit dataChanged(index, index);
}

void MissionPointMapItemModel::onCurrentItemChanged(int vehicleId,
                                                    const dto::MissionItemPtr& old,
                                                    const dto::MissionItemPtr& item)
{
    Q_UNUSED(vehicleId)

    QModelIndex index = this->itemIndex(old);
    if (index.isValid()) emit dataChanged(index, index, { ItemCurrent } );

    index = this->itemIndex(item);
    if (index.isValid()) emit dataChanged(index, index, { ItemCurrent } );
}

void MissionPointMapItemModel::onMissionChanged(const dto::MissionPtr& mission)
{
    for (const dto::MissionItemPtr& item: m_items)
    {
        if (item->missionId() != mission->id()) continue;

        QModelIndex index = this->itemIndex(item);
        if (index.isValid()) emit dataChanged(index, index);
    }
}

QHash<int, QByteArray> MissionPointMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ItemRole] = "itemPtr";
    roles[ItemCoordinateRole] = "itemCoordinate";
    roles[ItemVisibleRole] = "itemVisible";
    roles[ItemAcceptanceRadius] = "itemAcceptanceRadius";
    roles[ItemRadius] = "itemRadius";
    roles[ItemIndex] = "itemIndex";
    roles[ItemCurrent] = "itemCurrent";

    return roles;
}

QModelIndex MissionPointMapItemModel::itemIndex(const dto::MissionItemPtr& item) const
{
    return this->index(m_items.indexOf(item));
}
