#include "flight_presenter.h"

// Qt
#include <QMap>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

using namespace presentation;

class FlightPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    QMap<uint8_t, QString> vehiclesAlias;
};

FlightPresenter::FlightPresenter(domain::VehicleService* vehicleService,
                                 QObject* view):
    BasePresenter(view),
    d(new Impl())
{
    d->vehicleService = vehicleService;

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &FlightPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &FlightPresenter::onVehicleRemoved);

    for (uint8_t id: vehicleService->vehileIds())
        this->onVehicleAdded(id);
}

FlightPresenter::~FlightPresenter()
{
    delete d;
}

QStringList FlightPresenter::vehicles() const
{
    return d->vehiclesAlias.values();
}

QObject* FlightPresenter::vehicleObject(int index) const
{
    return d->vehicleService->vehicle(
                d->vehiclesAlias.key(d->vehiclesAlias.values().at(index)));
}

void FlightPresenter::onVehicleAdded(uint8_t id)
{
    d->vehiclesAlias[id] = tr("MAV %1").arg(id);
    emit vehiclesChanged();
}

void FlightPresenter::onVehicleRemoved(uint8_t id)
{
    d->vehiclesAlias.remove(id);
    emit vehiclesChanged();
}
