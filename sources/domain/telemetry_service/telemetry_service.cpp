#include "telemetry_service.h"

// Qt
#include <QMap>
#include <QTimerEvent>

// Internal
#include "settings_provider.h"

#include "db_facade.h"
#include "vehicle_description.h"

using namespace domain;

class TelemetryService::Impl
{
public:
    db::DbFacade* facade;

    QMap<int, bool> online;
    QMap<int, int> onlineTimers;
    QMap<int, Status> statuses;
    QMap<int, Availables> availables;
    QMap<int, Attitude> attitudes;
    QMap<int, Position> positions;
    QMap<int, Position> homePositions;
    QMap<int, Sns> snses;
    QMap<int, PowerSystem> powerSystems;
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

int TelemetryService::vehicleIdByMavId(int mavId) const
{
    return d->facade->vehicleIdByMavId(mavId);
}

bool TelemetryService::isOnline(int vehicleId)
{
    return d->online.value(vehicleId, false);
}

Status TelemetryService::status(int vehicleId) const
{
    return d->statuses.value(vehicleId);
}

Availables TelemetryService::availables(int vehicleId) const
{
    return d->availables.value(vehicleId);
}

Attitude TelemetryService::attitude(int vehicleId) const
{
    return d->attitudes.value(vehicleId);
}

Position TelemetryService::position(int vehicleId) const
{
    return d->positions.value(vehicleId);
}

Position TelemetryService::homePosition(int vehicleId) const
{
    return d->homePositions.value(vehicleId);
}

Sns TelemetryService::sns(int vehicleId) const
{
    return d->snses.value(vehicleId);
}

PowerSystem TelemetryService::powerSystem(int vehicleId) const
{
    return d->powerSystems.value(vehicleId);
}

void TelemetryService::setStatus(int vehicleId, const Status& status)
{
    if (d->statuses[vehicleId] == status) return;

    d->statuses[vehicleId] = status;
    emit statusChanged(vehicleId, status);
}

void TelemetryService::setOnline(int vehicleId, bool online)
{
    if (online)
    {
        int timerId = d->onlineTimers.key(vehicleId, -1);
        if (timerId != -1) this->killTimer(timerId);

        timerId = this->startTimer(SettingsProvider::value(
                                       settings::telemetry::timeout).toInt());
        d->onlineTimers[timerId] = vehicleId;
    }
    if (d->online[vehicleId] == online) return;

    d->online[vehicleId] = online;
    emit onlineChanged(online);
}

void TelemetryService::setAvailables(int vehicleId, const Availables& availables)
{
    if (d->availables[vehicleId] == availables) return;

    d->availables[vehicleId] = availables;
    emit availablesChanged(vehicleId, availables);
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

void TelemetryService::setPowerSystem(int vehicleId, const PowerSystem& powerSystem)
{
    if (d->powerSystems[vehicleId] == powerSystem) return;

    d->powerSystems[vehicleId] = powerSystem;
    emit powerSystemChanged(vehicleId, powerSystem);
}

void TelemetryService::timerEvent(QTimerEvent* event)
{
    if (!d->onlineTimers.contains(event->timerId())) return;

    this->setOnline(d->onlineTimers[event->timerId()], false);
    d->onlineTimers.remove(event->timerId());
    this->killTimer(event->timerId());
}

void TelemetryService::onVehicleRemoved(const db::VehicleDescriptionPtr& vehicle)
{
    d->statuses.remove(vehicle->id());
    d->attitudes.remove(vehicle->id());
    d->positions.remove(vehicle->id());
    d->homePositions.remove(vehicle->id());
    d->snses.remove(vehicle->id());
    d->powerSystems.remove(vehicle->id());
}
