#include "flight_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "map_item_model.h"
#include "vehicle.h"

using namespace presentation;

class FlightMapPresenter::Impl
{
public:
    MapItemModel mapModel;
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
    // TODO: update mark
    MapItem* item = new MapItem(vehicle->navigation().position(),
                                vehicle->attitude().yaw(),
                                QUrl("qrc:/indicators/plane_map_mark.svg"));
    d->mapModel.addMapItem(item);
/*
    connect(vehicle, &domain::Vehicle::navigationChanged, item,
            [item](domain::Navigation navigation) {
        item->setPosition(navigation.position);
    });*/
}

void FlightMapPresenter::removeVehicle(domain::Vehicle* vehicle)
{
    // TODO: remove vehicle
}

void FlightMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicles), QVariant::fromValue(&d->mapModel));
    // TODO: map actions on vehicle marks and routes
}
