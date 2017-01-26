#include "flight_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "mission_service.h"
#include "mission.h"
#include "vehicle_service.h"
#include "vehicle.h"

#include "mission_line_map_item_model.h"
#include "mission_point_map_item_model.h"
#include "vehicle_map_item_model.h"

using namespace presentation;

class FlightMapPresenter::Impl
{
public:
    domain::MissionService* missionService;
    domain::VehicleService* vehicleService;

    MissionLineMapItemModel lineModel;
    MissionPointMapItemModel pointModel;

    VehicleMapItemModel vehicleModel;
};

FlightMapPresenter::FlightMapPresenter(domain::MissionService* missionService,
                                       domain::VehicleService* vehicleService,
                                       QObject* parent):
    MapPresenter(parent),
    d(new Impl())
{
    d->missionService = missionService;
    d->vehicleService = vehicleService;

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &FlightMapPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &FlightMapPresenter::onVehicleRemoved);

    for (uint8_t id: vehicleService->vehileIds())
        this->onVehicleAdded(id);

    this->onMissionsChanged();
}

FlightMapPresenter::~FlightMapPresenter()
{
    delete d;
}

void FlightMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicleModel), QVariant::fromValue(&d->vehicleModel));
    this->setViewProperty(PROPERTY(lineModel), QVariant::fromValue(&d->lineModel));
    this->setViewProperty(PROPERTY(pointModel), QVariant::fromValue(&d->pointModel));
}

void FlightMapPresenter::onMissionsChanged()
{
    for (domain::Mission* mission: d->missionService->assignedMissions())
    {
        d->lineModel.addMission(mission);

        connect(mission, &domain::Mission::missionItemsChanged,
                this, &FlightMapPresenter::onMissionItemsChanged);
    }

    this->onMissionItemsChanged();
}

void FlightMapPresenter::onMissionItemsChanged()
{
    QList<domain::MissionItem*> items;

    for (domain::Mission* mission: d->missionService->assignedMissions())
    {
        items.append(mission->items());
    }

    d->pointModel.setMissionItems(items);
}

void FlightMapPresenter::onVehicleAdded(uint8_t id)
{
    d->vehicleModel.addVehicle(d->vehicleService->vehicle(id));
}

void FlightMapPresenter::onVehicleRemoved(uint8_t id)
{
    d->vehicleModel.removeVehicle(d->vehicleService->vehicle(id));
}
