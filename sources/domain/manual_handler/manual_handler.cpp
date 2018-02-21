#include "manual_handler.h"

// Qt
#include <QMap>
#include <QTimer>
#include <QDebug>

// Interval
#include "settings_provider.h"

#include "command.h"

#include "service_registry.h"
#include "command_service.h"

#include "joystick_controller.h"

using namespace domain;

class ManualHandler::Impl
{
public:
    domain::CommandService* service = domain::ServiceRegistry::commandService();
    JoystickController* controller = nullptr;
    QMap<int, ManualHandler::Axis> joystickAxes;

    int vehicleId = 0;

    QTimer timer;
    QMap<ManualHandler::Axis, float> impacts;
};

ManualHandler::ManualHandler(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    if (settings::Provider::value(settings::manual::joystick::enabled).toBool())
    {
        this->setJoystick(settings::Provider::value(settings::manual::joystick::device).toInt());
    }

    this->setEnabled(settings::Provider::value(settings::manual::enabled).toBool());
}

ManualHandler::~ManualHandler()
{
    connect(&d->timer, &QTimer::timeout, this, &ManualHandler::sendImpacts);
}

bool ManualHandler::enabled() const
{
    return d->timer.isActive();
}

bool ManualHandler::joystickEnabled() const
{
    return d->controller;
}

int ManualHandler::vehicleId() const
{
    return d->vehicleId;
}

float ManualHandler::impact(ManualHandler::Axis axis) const
{
    return d->impacts.value(axis, 0);
}

void ManualHandler::setEnabled(bool enabled)
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

void ManualHandler::setJoystick(int deviceId)
{
    if ((d->controller == nullptr) == (deviceId == -1)) return;

    if (deviceId > -1)
    {
        d->controller = new JoystickController(deviceId, this);
        connect(d->controller, &JoystickController::valueChanged,
                this, &ManualHandler::onControllerValueChanged);
        this->updateJoystickAxes();
    }
    else
    {
        delete d->controller;
    }

    emit joystickEnabledChanged(d->controller);
}

void ManualHandler::setVehicleId(int vehicleId)
{
    if (d->vehicleId == vehicleId) return;

    d->vehicleId = vehicleId;
    emit vehicleIdChanged(d->vehicleId);
}

void ManualHandler::updateJoystickAxes()
{
    d->joystickAxes.clear();

    d->joystickAxes[settings::Provider::value(settings::manual::joystick::pitchAxis).toInt()] = Pitch;
    d->joystickAxes[settings::Provider::value(settings::manual::joystick::rollAxis).toInt()] = Roll;
    d->joystickAxes[settings::Provider::value(settings::manual::joystick::yawAxis).toInt()] = Yaw;
    d->joystickAxes[settings::Provider::value(settings::manual::joystick::throttleAxis).toInt()] = Throttle;
}

void ManualHandler::setImpact(Axis axis, float impact)
{
    if (axis == NoneAxis || impact == d->impacts.value(axis, 0)) return;

    d->impacts[axis] = impact;
    emit impactChanged(axis, impact);
}

void ManualHandler::sendImpacts()
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

void ManualHandler::onControllerValueChanged(int axis, float value)
{
    this->setImpact(d->joystickAxes.value(axis, NoneAxis), value);
}
