#include "flight_map_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

using namespace presentation;

class FlightMapPresenter::Impl
{
public:
    QList<domain::Vehicle*> vehicles;
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
    d->vehicles.append(vehicle);
    this->updateVehicles();
}

void FlightMapPresenter::removeVehicle(domain::Vehicle* vehicle)
{
    d->vehicles.removeOne(vehicle);
    this->updateVehicles();
}

void FlightMapPresenter::updateVehicles()
{
    QList<QObject*> vehicles;

    for (domain::Vehicle* vehicle: d->vehicles)
        vehicles.append(vehicle);

    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(vehicles));
}

void FlightMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    // TODO: map actions on vehicle marks and routes
}
