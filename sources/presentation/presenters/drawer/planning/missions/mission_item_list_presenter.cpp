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
    QSortFilterProxyModel filterModel;
};

MissionItemListPresenter::MissionItemListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->filterModel.setSourceModel(&d->model);

    d->filterModel.setSortRole(MissionItemListModel::SequenceRole);
    d->filterModel.setDynamicSortFilter(true);
    d->filterModel.sort(0, Qt::AscendingOrder);

    connect(d->service, &domain::MissionService::missionItemAdded,
            this, [this](dto::MissionItemPtr item) {
        if (item->missionId() == d->missionId) d->model.addMissionItem(item);
    });
    connect(d->service, &domain::MissionService::missionItemRemoved,
            this, [this](dto::MissionItemPtr item) {
        if (item->missionId() == d->missionId) d->model.removeMissionItem(item);
    });
    connect(d->service, &domain::MissionService::missionItemChanged,
            this, [this](dto::MissionItemPtr item) {
        if (item->missionId() == d->missionId) d->model.updateMissionItem(item);
    });
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
    view->setProperty(PROPERTY(items), QVariant::fromValue(&d->filterModel));
}
