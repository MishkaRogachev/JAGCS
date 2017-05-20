#include "telemetry_service.h"

// Qt
#include <QMap>

// Internal
#include "vehicle_description.h"

using namespace domain;

class TelemetryService::Impl
{
public:
    QMap<int, Attitude> attitudes;
};

TelemetryService::TelemetryService(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

TelemetryService::~TelemetryService()
{}

Attitude TelemetryService::attitude(int vehicleId) const
{
    return d->attitudes[vehicleId];
}

void TelemetryService::setAttitude(int vehicleId, const Attitude& attitude)
{
    if (d->attitudes[vehicleId] == attitude) return;

    d->attitudes[vehicleId] = attitude;
    emit attitudeChanged(vehicleId, attitude);
}
