#include "mission_map_item_model.h"

// Internal
#include "mission_service.h"
#include "mission.h"

using namespace presentation;

class MissionMapItemModel::Impl
{
public:
    domain::MissionService* service;

    QList<uint8_t> missionIds;
};

MissionMapItemModel::MissionMapItemModel(domain::MissionService* service,
                                         QObject* parent):
    QAbstractListModel(parent),
    d(new Impl())
{
    d->service = service;

    connect(service, &domain::MissionService::missionAdded,
            this, &MissionMapItemModel::onMissionAdded);
    connect(service, &domain::MissionService::missionRemoved,
            this, &MissionMapItemModel::onMissionRemoved);

    for (uint8_t id: d->service->missionIds())
        this->onMissionAdded(id);
}

MissionMapItemModel::~MissionMapItemModel()
{
    delete d;
}

int MissionMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return d->missionIds.count();
}

QVariant MissionMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= d->missionIds.count()) return QVariant();

    domain::Mission* mission = d->service->mission(d->missionIds.at(index.row()));

    switch (role) {
    case MissionLineRole:
    {
        QVariantList line;
        for (domain::MissionItem* item: mission->items())
            line.append(QVariant::fromValue(item->coordinate()));
        break;
    }
    default:
        break;
    }
    //if (role != MissionItemRole) return;

    //mission->item()
}

void MissionMapItemModel::onMissionAdded(uint8_t id)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());

    domain::Mission* mission = d->service->mission(id);
    d->missionIds.append(id);

    connect(mission, &domain::Mission::missionItemAdded,
            this, &MissionMapItemModel::onMissionItemsChanged);
    connect(mission, &domain::Mission::missionItemRemoved,
            this, &MissionMapItemModel::onMissionItemsChanged);

    this->endInsertRows();
}

void MissionMapItemModel::onMissionRemoved(uint8_t id)
{
    int row = d->missionIds.indexOf(id);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    d->missionIds.removeOne(id);

    this->endRemoveRows();
}

void MissionMapItemModel::onMissionItemsChanged()
{
    uint8_t id = d->service->missionId(qobject_cast<domain::Mission*>(
                                           this->sender()));
    QModelIndex index = this->missionIndex(id);
    if (index.isValid()) emit dataChanged(index, index, { MissionLineRole });
}

QHash<int, QByteArray> MissionMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[MissionLineRole] = "missionLine";

    return roles;
}

QModelIndex MissionMapItemModel::missionIndex(uint8_t id) const
{
    return this->index(d->missionIds.indexOf(id));
}
