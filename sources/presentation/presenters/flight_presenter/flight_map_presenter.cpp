#include "flight_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "vehicle_service.h"
#include "abstract_vehicle.h"

using namespace presentation;

class FlightMapPresenter::Impl
{
public:
    domain::MissionService* missionService;
    domain::VehicleService* vehicleService;
};

FlightMapPresenter::FlightMapPresenter(domain::MissionService* missionService,
                                       domain::VehicleService* vehicleService,
                                       QObject* parent):
    MapPresenter(parent),
    d(new Impl())
{
    d->missionService = missionService;
    d->vehicleService = vehicleService;

    for (domain::Mission* mission: missionService->assignedMissions())
        this->addMission(mission);

    for (domain::AbstractVehicle* vehicle: vehicleService->vehicles())
        this->addVehicle(vehicle);

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &MapPresenter::addVehicle);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &MapPresenter::removeVehicle);

    connect(missionService, &domain::MissionService::missionAssigned,
            this, &MapPresenter::addMission);
    connect(missionService, &domain::MissionService::missionUnassigned,
            this, &MapPresenter::removeMission);
}

FlightMapPresenter::~FlightMapPresenter()
{
    delete d;
}

