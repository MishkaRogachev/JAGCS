#include "mission_line_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"

using namespace presentation;

MissionLineMapItemModel::MissionLineMapItemModel(domain::MissionService* service,
                                                 QObject* parent):
    QAbstractListModel(parent),
    m_service(service)
{
    connect(service, &domain::MissionService::missionAdded,
            this, &MissionLineMapItemModel::onMissionAdded);
    connect(service, &domain::MissionService::missionRemoved,
            this, &MissionLineMapItemModel::onMissionRemoved);
    connect(service, &domain::MissionService::missionItemChanged,
            this, &MissionLineMapItemModel::onMissionItemChanged);
    connect(service, &domain::MissionService::missionItemAdded,
            this, &MissionLineMapItemModel::onMissionItemChanged);
    connect(service, &domain::MissionService::missionItemRemoved,
            this, &MissionLineMapItemModel::onMissionItemChanged);

    for (const dao::MissionPtr& item: service->missions())
    {
        this->onMissionAdded(item);
    }
}

int MissionLineMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_missions.count();
}

QVariant MissionLineMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_missions.count()) return QVariant();

    const dao::MissionPtr& mission = m_missions.at(index.row());

    switch (role)
    {
    case MissionPathRole:
    {
        QVariantList line;
        for (const dao::MissionItemPtr& item: m_service->missionItems(mission->id()))
        {
            if (item->command() == dao::MissionItem::Home ||
                item->command() == dao::MissionItem::Waypoint ||
                item->command() == dao::MissionItem::Takeoff ||
                item->command() == dao::MissionItem::Landing ||
                item->command() == dao::MissionItem::LoiterUnlim ||
                item->command() == dao::MissionItem::LoiterAltitude ||
                item->command() == dao::MissionItem::LoiterTurns ||
                item->command() == dao::MissionItem::LoiterTime) // FIXME: bool hasCoordinate
            {
                QGeoCoordinate coordinate(item->latitude(), item->longitude());
                if (coordinate.isValid())
                {
                    line.append(QVariant::fromValue(coordinate));
                }
            }
            else if (item->command() == dao::MissionItem::Return && !line.isEmpty())
            {
                line.append(line[0]); // Return to home line
            }
        }
        return line;
    }
    default:
        return QVariant();
    }
}

void MissionLineMapItemModel::onMissionAdded(const dao::MissionPtr& mission)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_missions.append(mission);
    this->endInsertRows();
}

void MissionLineMapItemModel::onMissionRemoved(const dao::MissionPtr& mission)
{
    int row = m_missions.indexOf(mission);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_missions.removeOne(mission);
    this->endRemoveRows();
}

void MissionLineMapItemModel::onMissionItemChanged(const dao::MissionItemPtr& item)
{
    dao::MissionPtr mission = m_service->mission(item->missionId());
    QModelIndex index = this->index(m_missions.indexOf(mission));
    if (index.isValid()) emit dataChanged(index, index, { MissionPathRole });
}

QHash<int, QByteArray> MissionLineMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[MissionPathRole] = "missionPath";

    return roles;
}

QModelIndex MissionLineMapItemModel::missionIndex(const dao::MissionPtr& mission) const
{
    return this->index(m_missions.indexOf(mission));
}
