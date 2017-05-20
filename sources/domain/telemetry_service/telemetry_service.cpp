#include "telemetry_service.h"

// Qt
#include <QMap>

// Internal

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

Attitude TelemetryService::attitude(const db::VehicleDescriptionPtr& vehicle) const
{
    return d->attitudes[vehicle];
}

void TelemetryService::setAttitude(const db::VehicleDescriptionPtr& vehicle, const Attitude& attitude)
{
    if (d->attitudes[vehicle] == attitude) return;

    d->attitudes[vehicle] = attitude;
    emit attitudeChanged(vehicle, attitude);
}
