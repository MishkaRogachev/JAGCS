#include "manual_controller.h"

// Qt
#include <QMap>
#include <QTimer>
#include <QDebug>

// Interval
#include "settings_provider.h"

#include "command.h"

#include "service_registry.h"
#include "command_service.h"

using namespace domain;

class ManualController::Impl
{
public:
    domain::CommandService* service = domain::ServiceRegistry::commandService();

    int vehicleId = 0;

    QTimer timer;
    QMap<ManualController::Axis, float> impacts;
};

ManualController::ManualController(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

ManualController::~ManualController()
{
    connect(&d->timer, &QTimer::timeout, this, &ManualController::sendImpacts);
}

bool ManualController::enabled() const
{
    return d->timer.isActive();
}

void ManualController::setEnabled(bool enabled)
{
    if (d->timer.isActive() == enabled) return;

    if (enabled)
    {
        d->timer.start(settings::Provider::value(settings::manual::interval).toInt());
    }
    else
    {
        d->timer.stop();
    }
}

void ManualController::sentImpact(Axis axis, float impact)
{
    d->impacts[axis] = impact;
}

void ManualController::sendImpacts()
{
    dao::CommandPtr command = dao::CommandPtr::create();

    command->setType(dao::Command::ManualImpacts);
    command->setArguments({
                              d->impacts.value(Pitch, 0),
                              d->impacts.value(Roll, 0),
                              d->impacts.value(Yaw, 0),
                              d->impacts.value(Throttle, 0),
                          });

    d->service->executeCommand(d->vehicleId, command);
}
