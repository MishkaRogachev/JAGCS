#include "joystick_controller.h"

// Qt
#include <QGamepadManager>
#include <QGamepad>
#include <QDebug>

using namespace domain;

class JoystickController::Impl
{
public:
    QGamepad* pad = nullptr;
};

JoystickController::JoystickController(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

JoystickController::~JoystickController()
{
    delete d;
}

void JoystickController::init()
{
    auto pads = QGamepadManager::instance()->connectedGamepads();

    if (!pads.isEmpty())
    {
        d->pad = new QGamepad(pads.first(), this);

        connect(d->pad, &QGamepad::axisLeftXChanged, this, &JoystickController::axisXChanged);
        connect(d->pad, &QGamepad::axisLeftYChanged, this, &JoystickController::axisYChanged);
        connect(d->pad, &QGamepad::axisRightXChanged, this, &JoystickController::axisZChanged);
        connect(d->pad, &QGamepad::axisRightYChanged, this, &JoystickController::axisRChanged);
    }
}

double JoystickController::axisX() const
{
    return d->pad ? d->pad->axisLeftX() : 0;
}

double JoystickController::axisY() const
{
    return d->pad ? d->pad->axisLeftY() : 0;
}

double JoystickController::axisZ() const
{
    return d->pad ? d->pad->axisRightX() : 0;
}

double JoystickController::axisR() const
{
    return d->pad ? d->pad->axisRightY() : 0;
}
