#include "joystick_controller.h"

// Qt
#include <QGamepad>
#include <QDebug>

using namespace domain;

class JoystickController::Impl
{
public:
    QGamepad* pad;
};

JoystickController::JoystickController(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->pad = new QGamepad(0, this);

    connect(d->pad, &QGamepad::axisLeftXChanged, this, &JoystickController::axisXChanged);
    connect(d->pad, &QGamepad::axisLeftYChanged, this, &JoystickController::axisYChanged);
    connect(d->pad, &QGamepad::axisRightXChanged, this, &JoystickController::axisZChanged);
    connect(d->pad, &QGamepad::axisRightYChanged, this, &JoystickController::axisRChanged);
}

JoystickController::~JoystickController()
{
    delete d;
}

double JoystickController::axisX() const
{
    return d->pad->axisLeftX();
}

double JoystickController::axisY() const
{
    return d->pad->axisLeftY();
}

double JoystickController::axisZ() const
{
    return d->pad->axisRightX();
}

double JoystickController::axisR() const
{
    return d->pad->axisRightY();
}
