#include "joystick_controller.h"

// Qt
#ifdef WITH_GAMEPAD
#include <QGamepad>
# endif

#include <QDebug>

using namespace domain;

JoystickController::JoystickController(int device, QObject* parent):
    QObject(parent)
{
#ifdef WITH_GAMEPAD
    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (device > -1 && device < gamepads.count())
    {
        m_gamepad = new QGamepad(gamepads[device], this);
        m_gamepad->setDeviceId(gamepads[device]);
    }
    else
    {
        m_gamepad = new QGamepad(0, this);
    }

    connect(m_gamepad, &QGamepad::axisLeftXChanged, this, [this](double value) {
            emit valueChanged(1, value);
    });
    connect(m_gamepad, &QGamepad::axisLeftYChanged, this, [this](double value) {
            emit valueChanged(2, value);
    });
    connect(m_gamepad, &QGamepad::axisRightXChanged, this, [this](double value) {
            emit valueChanged(3, value);
    });
    connect(m_gamepad, &QGamepad::axisRightYChanged, this, [this](double value) {
            emit valueChanged(4, value);
    });
# endif
}

float JoystickController::value(int axis) const
{
    switch (axis)
    {
#ifdef WITH_GAMEPAD
    case 1: return m_gamepad->axisLeftX();
    case 2: return m_gamepad->axisLeftY();
    case 3: return m_gamepad->axisRightX();
    case 4: return m_gamepad->axisRightY();
# endif
    default: return 0;
    }
}
