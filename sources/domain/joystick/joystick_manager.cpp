#include "joystick_manager.h"

// Qt
#include <QMap>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "service_registry.h"
#include "vehicle_service.h"

#include "joystick_controller.h"

using namespace domain;

class JoystickManager::Impl
{
public:
    domain::VehicleService* vehicleService = domain::ServiceRegistry::vehicleService();
    int vehicleId = 0;

    const JoystickController* controller;
    QMap<int, float> axes;
};

JoystickManager::JoystickManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->controller = new JoystickController(
                        settings::Provider::value(settings::manual::joystick::device).toInt(),
                        this);
    connect(d->controller, &JoystickController::valueChanged,
            this, &JoystickManager::overrideValue);
}

JoystickManager::~JoystickManager()
{}

float JoystickManager::value(int axis) const
{
    return d->axes.value(axis, 0);
}

void JoystickManager::overrideValue(int axis, float value)
{
    d->axes[axis] = value;
    if (d->vehicleId) this->sendCurrentDeviation();

    emit valueChanged(axis, value);
}

void JoystickManager::setControlVehicle(int vehicleId)
{
    d->vehicleId = vehicleId;
}

void JoystickManager::sendCurrentDeviation()
{
    float pitch = this->value(settings::Provider::value(settings::manual::joystick::pitchAxis, 0).toInt());
    float roll = this->value(settings::Provider::value(settings::manual::joystick::rollAxis, 0).toInt());
    float throttle = this->value(settings::Provider::value(settings::manual::joystick::throttleAxis, 0).toInt());
    float yaw = this->value(settings::Provider::value(settings::manual::joystick::yawAxis, 0).toInt());

    d->vehicleService->sendManualControl(d->vehicleId, pitch, roll, throttle, yaw);
}
