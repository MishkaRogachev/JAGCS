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
    const double maxImpact = 1.0;
}

using namespace domain;

const QList<ManualController::Axis> ManualController::axes({
    ManualController::Pitch,
    ManualController::Roll,
    ManualController::Yaw,
    ManualController::Throttle
});

class ManualController::Impl
{
public:
    domain::CommandService* service = domain::ServiceRegistry::commandService();

    #ifdef WITH_GAMEPAD
    JoystickController* controller = nullptr;
    QMap<ManualController::Axis, int> joystickAxes;
    QMap<ManualController::Axis, double> joystickFactors;
    # endif

    int vehicleId = 0;

    QTimer timer;
    QMap<ManualController::Axis, double> impacts;
};

ManualController::ManualController(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    connect(&d->timer, &QTimer::timeout, this, &ManualController::onTimeout);

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

double ManualController::impact(ManualController::Axis axis) const
{
    return d->impacts.value(axis, qQNaN());
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

        this->clearImpacts();
        this->sendImpacts();
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
        d->controller->setDeviceId(settings::Provider::value(settings::manual::joystick::device).toInt());
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

    d->joystickAxes[Pitch] = settings::Provider::value(
                                 settings::manual::joystick::pitch::axis).toInt();
    d->joystickAxes[Roll] = settings::Provider::value(
                                settings::manual::joystick::roll::axis).toInt();
    d->joystickAxes[Yaw] = settings::Provider::value(
                               settings::manual::joystick::yaw::axis).toInt();
    d->joystickAxes[Throttle] = settings::Provider::value(
                                    settings::manual::joystick::throttle::axis).toInt();

    d->joystickFactors.clear();

    d->joystickAxes[Pitch] = settings::Provider::value(
                                 settings::manual::joystick::pitch::factor).toInt() * 0.01;
    d->joystickAxes[Roll] = settings::Provider::value(
                                settings::manual::joystick::roll::factor).toInt() * 0.01;
    d->joystickAxes[Yaw] = settings::Provider::value(
                               settings::manual::joystick::yaw::factor).toInt() * 0.01;
    d->joystickAxes[Throttle] = settings::Provider::value(
                                    settings::manual::joystick::throttle::factor).toInt() * 0.01;
# endif
}

void ManualController::setImpact(Axis axis, double impact)
{
    double impactScaled = qMax(qMin(impact, ::maxImpact), -::maxImpact);

    if (axis == NoneAxis || impactScaled == d->impacts.value(axis, qQNaN())) return;

    d->impacts[axis] = impactScaled;
    emit impactChanged(axis, impactScaled);
}

void ManualController::addImpact(ManualController::Axis axis, double impact)
{
    double current = this->impact(axis);
    this->setImpact(axis, qIsNaN(current) ? impact : current + impact);
}

void ManualController::clearImpacts()
{
    d->impacts.clear();

    for (Axis axis: axes) emit impactChanged(axis, this->impact(axis));
}

void ManualController::sendImpacts()
{
    if (d->vehicleId == 0) return;

    dao::CommandPtr command = dao::CommandPtr::create();
    command->setType(dao::Command::ManualImpacts);

    for (Axis axis: axes) command->addArgument(this->impact(axis));

    d->service->executeCommand(d->vehicleId, command);
}

void ManualController::onTimeout()
{
#ifdef WITH_GAMEPAD
    if (d->controller)
    {
        for (Axis axis: axes)
        {
            double value = d->controller->value(d->joystickAxes.value(axis, -1)) *
                           d->joystickFactors.value(axis, 0.0);
            if (!qFuzzyIsNull(value)) this->addImpact(axis, value);
        }
    }
# endif

    this->sendImpacts();
}
