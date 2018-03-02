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

#ifdef WITH_GAMEPAD
#include "joystick_controller.h"
# endif

namespace
{
    const float maxImpact = 1.0;
}

using namespace domain;

class ManualController::Impl
{
public:
    domain::CommandService* service = domain::ServiceRegistry::commandService();

    #ifdef WITH_GAMEPAD
    JoystickController* controller = nullptr;
    QMap<int, ManualController::Axis> joystickAxes;
    # endif

    int vehicleId = 0;

    QTimer timer;
    QMap<ManualController::Axis, float> impacts;
};

ManualController::ManualController(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    connect(&d->timer, &QTimer::timeout, this, &ManualController::sendImpacts);

#ifdef WITH_GAMEPAD
    if (settings::Provider::value(settings::manual::joystick::enabled).toBool())
    {
        this->setJoystickEnabled(settings::Provider::value(
                                     settings::manual::joystick::enabled).toBool());
    }
# endif

    if (settings::Provider::value(settings::manual::enabled).toBool()) this->setEnabled(true);
}

ManualController::~ManualController()
{}

bool ManualController::enabled() const
{
    return d->timer.isActive();
}

bool ManualController::joystickEnabled() const
{
#ifdef WITH_GAMEPAD
    return d->controller;
#else
    return false;
# endif
}

int ManualController::vehicleId() const
{
    return d->vehicleId;
}

float ManualController::impact(ManualController::Axis axis) const
{
    return d->impacts.value(axis, 0);
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

    emit enabledChanged(this->enabled());
}

void ManualController::setJoystickEnabled(bool enabled)
{
#ifdef WITH_GAMEPAD
    if ((d->controller != nullptr) == enabled) return;

    if (enabled)
    {
        d->controller = new JoystickController(this);
        d->controller->setDeviceId(settings::Provider::value(
                                       settings::manual::joystick::device).toInt());
        connect(d->controller, &JoystickController::valueChanged,
                this, &ManualController::onControllerValueChanged);
        this->updateJoystickAxes();
    }
    else
    {
        delete d->controller;
        d->controller = nullptr;
    }
#else
    Q_UNUSED(enabled)
# endif
}

void ManualController::setJoystickDevice(int deviceId)
{
#ifdef WITH_GAMEPAD
    if (d->controller) d->controller->setDeviceId(deviceId);
#else
    Q_UNUSED(deviceId)
# endif
}

void ManualController::setVehicleId(int vehicleId)
{
    if (d->vehicleId == vehicleId) return;

    d->vehicleId = vehicleId;
    emit vehicleIdChanged(d->vehicleId);
}

void ManualController::updateJoystickAxes()
{
#ifdef WITH_GAMEPAD
    d->joystickAxes.clear();

    d->joystickAxes[settings::Provider::value(settings::manual::joystick::pitchAxis).toInt()] = Pitch;
    d->joystickAxes[settings::Provider::value(settings::manual::joystick::rollAxis).toInt()] = Roll;
    d->joystickAxes[settings::Provider::value(settings::manual::joystick::yawAxis).toInt()] = Yaw;
    d->joystickAxes[settings::Provider::value(settings::manual::joystick::throttleAxis).toInt()] = Throttle;
# endif
}

void ManualController::setImpact(Axis axis, float impact)
{
    float impactScaled = qMax(qMin(impact, ::maxImpact), -::maxImpact);

    if (axis == NoneAxis ||
        impactScaled == d->impacts.value(axis, 0)) return;

    d->impacts[axis] = impactScaled;
    emit impactChanged(axis, impactScaled);
}

void ManualController::addImpact(ManualController::Axis axis, float impact)
{
    this->setImpact(axis, this->impact(axis) + impact);
}

void ManualController::sendImpacts()
{
    if (d->vehicleId == 0) return;

    dao::CommandPtr command = dao::CommandPtr::create();

    command->setType(dao::Command::ManualImpacts);
    command->setArguments({ this->impact(Pitch), this->impact(Roll),
                            this->impact(Yaw), this->impact(Throttle) });

    d->service->executeCommand(d->vehicleId, command);
}

void ManualController::onControllerValueChanged(int axis, float value)
{
#ifdef WITH_GAMEPAD
    this->setImpact(d->joystickAxes.value(axis, NoneAxis), value);
#else
    Q_UNUSED(axis)
    Q_UNUSED(value)
# endif
}
