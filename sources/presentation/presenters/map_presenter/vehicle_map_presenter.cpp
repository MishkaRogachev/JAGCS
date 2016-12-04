#include "vehicle_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "vehicle_map_item_model.h"

using namespace presentation;

class VehicleMapPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    VehicleMapItemModel vehicleModel;
};

VehicleMapPresenter::VehicleMapPresenter(domain::VehicleService* vehicleService,
                                         QObject* parent):
    MapPresenter(parent),
    d(new Impl())
{
    d->vehicleService = vehicleService;

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &VehicleMapPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &VehicleMapPresenter::onVehicleRemoved);

    for (uint8_t id: vehicleService->vehileIds())
        this->onVehicleAdded(id);
}

VehicleMapPresenter::~VehicleMapPresenter()
{
    delete d;
}

void VehicleMapPresenter::connectView(QObject* view)
{
    MapPresenter::connectView(view);

    this->setViewProperty(PROPERTY(vehicleModel),
                          QVariant::fromValue(&d->vehicleModel));

    connect(view, SIGNAL(setHome(QVariant)), this, SLOT(onSetHome(QVariant)));
}

void VehicleMapPresenter::onVehicleAdded(uint8_t id)
{
    d->vehicleModel.addVehicle(d->vehicleService->vehicle(id));
}

void VehicleMapPresenter::onVehicleRemoved(uint8_t id)
{
    // TODO: correct Vehicle removing
    d->vehicleModel.removeVehicle(d->vehicleService->vehicle(id));
}

void VehicleMapPresenter::onSetHome(const QVariant& position)
{
    QGeoCoordinate coordinate = position.value<QGeoCoordinate>();
    if (!coordinate.isValid()) return;

    for (domain::Vehicle* vehicle: d->vehicleService->vehicles())
    {
        emit vehicle->commandSetHome(domain::Position(coordinate));
    }
}
