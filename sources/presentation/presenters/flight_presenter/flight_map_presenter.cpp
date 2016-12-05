#include "flight_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "vehicle_map_item_model.h"

using namespace presentation;

class FlightMapPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    VehicleMapItemModel vehicleModel;
};

FlightMapPresenter::FlightMapPresenter(domain::VehicleService* vehicleService,
                                       QObject* parent):
    MapPresenter(parent),
    d(new Impl())
{
    d->vehicleService = vehicleService;

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &FlightMapPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &FlightMapPresenter::onVehicleRemoved);

    for (uint8_t id: vehicleService->vehileIds())
        this->onVehicleAdded(id);
}

FlightMapPresenter::~FlightMapPresenter()
{
    delete d;
}

void FlightMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicleModel),
                          QVariant::fromValue(&d->vehicleModel));
}

void FlightMapPresenter::onVehicleAdded(uint8_t id)
{
    d->vehicleModel.addVehicle(d->vehicleService->vehicle(id));
}

void FlightMapPresenter::onVehicleRemoved(uint8_t id)
{
    // TODO: correct Vehicle removing
    d->vehicleModel.removeVehicle(d->vehicleService->vehicle(id));
}
