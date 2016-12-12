#include "mission_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"

#include "mission_line_map_item_model.h"
#include "mission_point_map_item_model.h"

using namespace presentation;

class MissionMapPresenter::Impl
{
public:
    domain::MissionService* missionService;

    MissionLineMapItemModel lineModel;
    MissionPointMapItemModel pointModel;

    Impl(domain::MissionService* missionService):
        missionService(missionService),
        lineModel(missionService)
    {}
};

MissionMapPresenter::MissionMapPresenter(domain::MissionService* missionService,
                                         QObject* parent):
    MapPresenter(parent),
    d(new Impl(missionService))
{
    connect(missionService, &domain::MissionService::missionAdded,
            this, &MissionMapPresenter::onMissionAdded);
    connect(missionService, &domain::MissionService::missionRemoved,
            this, &MissionMapPresenter::onMissionRemoved);

    for (uint8_t id: missionService->missionIds())
        this->onMissionAdded(id);
}

MissionMapPresenter::~MissionMapPresenter()
{
    delete d;
}

void MissionMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    this->setViewProperty(PROPERTY(lineModel), QVariant::fromValue(&d->lineModel));
    this->setViewProperty(PROPERTY(pointModel), QVariant::fromValue(&d->pointModel));
}

void MissionMapPresenter::onMissionAdded(uint8_t id)
{
    domain::Mission* mission = d->missionService->mission(id);
    d->lineModel.addMission(mission);

    connect(mission, &domain::Mission::missionItemAdded,
            &d->pointModel, &MissionPointMapItemModel::addMissionItem);
    connect(mission, &domain::Mission::missionItemRemoved,
            &d->pointModel, &MissionPointMapItemModel::removeMissionItem);

    for (domain::MissionItem* item: mission->items())
        d->pointModel.addMissionItem(item);
}

void MissionMapPresenter::onMissionRemoved(uint8_t id)
{
    domain::Mission* mission = d->missionService->mission(id);
    d->lineModel.removeMission(mission);

    disconnect(mission, 0, this, 0);

    for (domain::MissionItem* item: mission->items())
        d->pointModel.removeMissionItem(item);
}
