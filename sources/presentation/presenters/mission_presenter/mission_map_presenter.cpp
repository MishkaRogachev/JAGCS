#include "mission_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "vehicle_service.h"
#include "vehicle.h"

using namespace presentation;

class MissionMapPresenter::Impl
{
public:
    domain::MissionService* missionService;
    domain::VehicleService* vehicleService;
};

MissionMapPresenter::MissionMapPresenter(domain::MissionService* missionService,
                                         domain::VehicleService* vehicleService,
                                         QObject* parent):
    MapPresenter(parent),
    d(new Impl())
{
    d->missionService = missionService;
    d->vehicleService = vehicleService;

    for (domain::Mission* mission: missionService->missions())
        this->addMission(mission);

    for (domain::Vehicle* vehicle: vehicleService->vehicles())
        this->addVehicle(vehicle);

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &MapPresenter::addVehicle);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &MapPresenter::removeVehicle);

    connect(missionService, &domain::MissionService::missionAdded,
            this, &MapPresenter::addMission);
    connect(missionService, &domain::MissionService::missionRemoved,
            this, &MapPresenter::removeMission);
}

MissionMapPresenter::~MissionMapPresenter()
{
    delete d;
}
