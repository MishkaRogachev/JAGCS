#include "mission_list_model.h"

// Qt
#include <QDebug>

// Internal
#include "mission.h"

using namespace presentation;

MissionListModel::MissionListModel(QObject* parent):
    QAbstractListModel(parent)
{}

int MissionListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_missions.count();
}

QVariant MissionListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_missions.count()) return QVariant();

    dto::MissionPtr mission = m_missions.at(index.row());

    switch (role)
    {
    case MissionIdRole: return mission->id();
    case MissionNameRole: return mission->name();
    default: return QVariant();
    }
}

void MissionListModel::setMissions(const dto::MissionPtrList& missions)
{
    this->beginResetModel();
    m_missions = missions;
    this->endResetModel();
}

void MissionListModel::addMission(const dto::MissionPtr& mission)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_missions.append(mission);
    this->endInsertRows();
}

void MissionListModel::updateMission(const dto::MissionPtr& mission)
{
    QModelIndex index = this->index(m_missions.indexOf(mission));
    if (!index.isValid()) return;

    emit dataChanged(index, index, { MissionNameRole });
}

void MissionListModel::removeMission(const dto::MissionPtr& mission)
{
    int row = m_missions.indexOf(mission);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_missions.removeOne(mission);
    this->endRemoveRows();
}

QHash<int, QByteArray> MissionListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[MissionIdRole] = "missionId";
    roles[MissionNameRole] = "missionName";

    return roles;
}
