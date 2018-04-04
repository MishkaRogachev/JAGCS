#include "mission_line_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"
#include "mission_item.h"

#include "mission_service.h"
#include "mission_assignment.h"

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
    connect(service, &domain::MissionService::missionChanged,
            this, &MissionLineMapItemModel::onMissionChanged);

    connect(service, &domain::MissionService::assignmentAdded,
            this, &MissionLineMapItemModel::onAssignmentChanged);
    connect(service, &domain::MissionService::assignmentRemoved,
            this, &MissionLineMapItemModel::onAssignmentChanged);
    connect(service, &domain::MissionService::assignmentChanged,
            this, &MissionLineMapItemModel::onAssignmentChanged);

    connect(service, &domain::MissionService::missionItemChanged,
            this, &MissionLineMapItemModel::onMissionItemChanged);
    connect(service, &domain::MissionService::missionItemAdded,
            this, &MissionLineMapItemModel::onMissionItemChanged);
    connect(service, &domain::MissionService::missionItemRemoved,
            this, &MissionLineMapItemModel::onMissionItemChanged);

    for (const dto::MissionPtr& item: service->missions())
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

    const dto::MissionPtr& mission = m_missions.at(index.row());
    switch (role)
    {
    case MissionPathRole:
    {
        QVariantList line;
        if (!settings::Provider::value(settings::mission::mission + QString::number(mission->id()) +
                                       "/" + settings::visibility).toBool())
        {
            line.append(QVariant::fromValue(QGeoCoordinate(0, 0)));
            return line;
        }

        for (const dto::MissionItemPtr& item: m_service->missionItems(mission->id()))
        {
            if (item->isPositionatedItem())
            {
                if (item->coordinate().isValid())
                {
                    line.append(QVariant::fromValue(item->coordinate()));
                }
            }
            else if (item->command() == dto::MissionItem::Return && !line.isEmpty())
            {
                line.append(line[0]); // Return to home line
            }
        }
        return line;
    }
    case MissionStatusRole:
    {
        dto::MissionAssignmentPtr assignment  = m_service->missionAssignment(mission->id());
        if (assignment.isNull()) return -1;

        return assignment->status();
    }
    default:
        return QVariant();
    }
}

void MissionLineMapItemModel::onMissionAdded(const dto::MissionPtr& mission)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_missions.append(mission);
    this->endInsertRows();
}

void MissionLineMapItemModel::onMissionRemoved(const dto::MissionPtr& mission)
{
    int row = m_missions.indexOf(mission);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_missions.removeOne(mission);
    this->endRemoveRows();
}

void MissionLineMapItemModel::onMissionChanged(const dto::MissionPtr& mission)
{
    QModelIndex index = this->index(m_missions.indexOf(mission));
    if (index.isValid()) emit dataChanged(index, index, { MissionPathRole });
}

void MissionLineMapItemModel::onAssignmentChanged(const dto::MissionAssignmentPtr& assignment)
{
    for (int row = 0 ; row < m_missions.count(); ++row)
    {
        if (m_missions[row]->id() != assignment->missionId()) continue;

        QModelIndex index = this->index(row);
        if (index.isValid()) emit dataChanged(index, index, { MissionPathRole });
        return;
    }
}

void MissionLineMapItemModel::onMissionItemChanged(const dto::MissionItemPtr& item)
{
    dto::MissionPtr mission = m_service->mission(item->missionId());
    QModelIndex index = this->index(m_missions.indexOf(mission));
    if (index.isValid()) emit dataChanged(index, index, { MissionPathRole });
}

QHash<int, QByteArray> MissionLineMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[MissionPathRole] = "missionPath";
    roles[MissionStatusRole] = "missionStatus";

    return roles;
}

QModelIndex MissionLineMapItemModel::missionIndex(const dto::MissionPtr& mission) const
{
    return this->index(m_missions.indexOf(mission));
}
