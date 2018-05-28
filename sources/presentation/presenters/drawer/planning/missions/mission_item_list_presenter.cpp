#include "mission_item_list_presenter.h"

// Qt
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission.h"
#include "mission_item.h"

#include "service_registry.h"
#include "mission_service.h"

#include "mission_item_list_model.h"

using namespace presentation;

class MissionItemListPresenter::Impl
{
public:
    domain::MissionService* const service = serviceRegistry->missionService();
    int missionId = 0;

    MissionItemListModel model;
    QSortFilterProxyModel sortModel;
};

MissionItemListPresenter::MissionItemListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->sortModel.setSourceModel(&d->model);

    d->sortModel.setSortRole(MissionItemListModel::SequenceRole);
    d->sortModel.setDynamicSortFilter(true);
    d->sortModel.sort(0, Qt::AscendingOrder);

    connect(d->service, &domain::MissionService::missionItemAdded,
            &d->model, &MissionItemListModel::addMissionItem);
    connect(d->service, &domain::MissionService::missionItemRemoved,
            &d->model, &MissionItemListModel::removeMissionItem);
    connect(d->service, &domain::MissionService::missionItemChanged,
            &d->model, &MissionItemListModel::updateMissionItem);
}

MissionItemListPresenter::~MissionItemListPresenter()
{}

void MissionItemListPresenter::setMission(int id)
{
    if (d->missionId == id) return;

    d->missionId = id;
    d->model.setMissionItems(d->service->missionItems(d->missionId));
}

void MissionItemListPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(items), QVariant::fromValue(&d->sortModel));
}
