#include "mission_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"

#include "mission_line_map_item_model.h"

using namespace presentation;

class MissionMapPresenter::Impl
{
public:
    domain::MissionService* missionService;

    MissionLineMapItemModel lineModel;

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

    this->setViewProperty(PROPERTY(lineModel),
                          QVariant::fromValue(&d->lineModel));
}

void MissionMapPresenter::onMissionAdded(uint8_t id)
{
    d->lineModel.addMission(d->missionService->mission(id));
}

void MissionMapPresenter::onMissionRemoved(uint8_t id)
{
    // TODO: correct Mission removing
    d->lineModel.removeMission(d->missionService->mission(id));
}
