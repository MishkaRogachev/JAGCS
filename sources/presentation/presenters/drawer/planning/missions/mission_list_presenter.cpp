#include "mission_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "mission.h"

#include "service_registry.h"
#include "mission_service.h"

#include "mission_list_model.h"
#include "mission_list_filter_model.h"

using namespace presentation;

class MissionListPresenter::Impl
{
public:
    domain::MissionService* const service = serviceRegistry->missionService();

    MissionListModel missionsModel;
    MissionListFilterModel sortingModel;
};

MissionListPresenter::MissionListPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->missionsModel.setMissions(d->service->missions());
    d->sortingModel.setSourceModel(&d->missionsModel);

    connect(d->service, &domain::MissionService::missionAdded,
            &d->missionsModel, &MissionListModel::addMission);
    connect(d->service, &domain::MissionService::missionRemoved,
            &d->missionsModel, &MissionListModel::removeMission);
    connect(d->service, &domain::MissionService::missionChanged,
            &d->missionsModel, &MissionListModel::updateMission);
}

MissionListPresenter::~MissionListPresenter()
{}

void MissionListPresenter::addMission()
{
    d->service->addNewMission(tr("New Mission"));
}

void MissionListPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->setViewProperty(PROPERTY(missions), QVariant::fromValue(&d->sortingModel));
}
