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
};

MissionMapPresenter::MissionMapPresenter(domain::MissionService* missionService,
                                         domain::VehicleService* vehicleService,
                                         QObject* parent):
    MapPresenter(parent),
    d(new Impl())
{
    d->missionService = missionService;

    connect(missionService, &domain::MissionService::missionAdded,
            this, &MissionMapPresenter::onMissionAdded);
    connect(missionService, &domain::MissionService::missionRemoved,
            this, &MissionMapPresenter::onMissionRemoved);

    for (domain::Mission* mission: missionService->missions())
        this->onMissionAdded(mission);
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

void MissionMapPresenter::onMissionAdded(domain::Mission* mission)
{
    d->lineModel.addMission(mission);

    connect(mission, &domain::Mission::missionItemsChanged,
            this, &MissionMapPresenter::onMissionItemsChanged);

    this->onMissionItemsChanged();
}

void MissionMapPresenter::onMissionRemoved(domain::Mission* mission)
{
    d->lineModel.removeMission(mission);

    disconnect(mission, 0, this, 0);

    this->onMissionItemsChanged();
}

void MissionMapPresenter::onMissionItemsChanged()
{
    QList<domain::MissionItem*> items;

    for (domain::Mission* mission: d->missionService->missions())
    {
        items.append(mission->items());
    }

    d->pointModel.setMissionItems(items);
}
