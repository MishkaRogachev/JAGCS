#include "telemetry_service.h"

// Qt
#include <QMap>

// Internal
#include "db_facade.h"
#include "vehicle_description.h"

using namespace domain;

class TelemetryService::Impl
{
public:
    db::DbFacade* facade;

    QMap<int, Attitude> attitudes;
    QMap<int, Position> positions;
    QMap<int, Position> homePositions;
    QMap<int, Sns> snses;
};

TelemetryService::TelemetryService(db::DbFacade* facade, QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->facade = facade;

    connect(d->facade, &db::DbFacade::vehicleRemoved, this, &TelemetryService::onVehicleRemoved);
}

TelemetryService::~TelemetryService()
{}

Attitude TelemetryService::attitude(int vehicleId) const
{
    return d->attitudes[vehicleId];
}

Position TelemetryService::position(int vehicleId) const
{
    return d->positions[vehicleId];
}

Position TelemetryService::homePosition(int vehicleId) const
{
    return d->homePositions[vehicleId];
}

Sns TelemetryService::sns(int vehicleId) const
{
    return d->snses[vehicleId];
}

void TelemetryService::setAttitude(int vehicleId, const Attitude& attitude)
{
    if (d->attitudes[vehicleId] == attitude) return;

    d->attitudes[vehicleId] = attitude;
    emit attitudeChanged(vehicleId, attitude);
}

void TelemetryService::setPosition(int vehicleId, const Position& position)
{
    if (d->positions[vehicleId] == position) return;

    d->positions[vehicleId] = position;
    emit positionChanged(vehicleId, position);
}

void TelemetryService::setHomePosition(int vehicleId, const Position& position)
{
    if (d->homePositions[vehicleId] == position) return;

    d->homePositions[vehicleId] = position;
    emit homePositionChanged(vehicleId, position);
}

void TelemetryService::setSns(int vehicleId, const Sns& sns)
{
    if (d->snses[vehicleId] == sns) return;

    d->snses[vehicleId] = sns;
    emit snsChanged(vehicleId, sns);
}

void TelemetryService::onVehicleRemoved(const db::VehicleDescriptionPtr& vehicle)
{
    d->attitudes.remove(vehicle->id());
    d->positions.remove(vehicle->id());
    d->homePositions.remove(vehicle->id());
    d->snses.remove(vehicle->id());
}
