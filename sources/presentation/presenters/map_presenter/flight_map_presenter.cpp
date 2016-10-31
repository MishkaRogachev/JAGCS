#include "flight_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_map_item_model.h"
#include "vehicle.h"

using namespace presentation;

class FlightMapPresenter::Impl
{
public:
    VehicleMapItemModel vehicleModel;
};

FlightMapPresenter::FlightMapPresenter(QObject* parent):
    MapPresenter(parent),
    d(new Impl())
{}

FlightMapPresenter::~FlightMapPresenter()
{
    delete d;
}

void FlightMapPresenter::addVehicle(domain::Vehicle* vehicle)
{
    d->vehicleModel.addVehicle(vehicle);
}

void FlightMapPresenter::removeVehicle(domain::Vehicle* vehicle)
{
    d->vehicleModel.removeVehicle(vehicle);
}

void FlightMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicleModel),
                          QVariant::fromValue(&d->vehicleModel));
    // TODO: map actions on vehicle marks and routes
}
