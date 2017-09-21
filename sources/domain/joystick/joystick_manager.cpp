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
    d->controller = new JoystickController(settings::Provider::value(settings::joystick::device).toInt(),
                                           this);
    connect(d->controller, &JoystickController::valueChanged,
            this, &JoystickManager::overrideValue);
}

JoystickManager::~JoystickManager()
{}

float JoystickManager::value(int axis) const
{
    return d->axes.value(axis, NAN);
}

void JoystickManager::overrideValue(int axis, float value)
{
    d->axes[axis] = value;

    if (d->vehicleId)
    {
        d->vehicleService->sendManualControl(d->vehicleId, this->value(0), this->value(1),
                                             this->value(1), this->value(2));
    }

    emit valueChanged(axis, value);
}

void JoystickManager::setControlVehicle(int vehicleId)
{
    d->vehicleId = vehicleId;
}
