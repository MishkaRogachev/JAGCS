#ifndef JOYSTICK_CONTROLLER_H
#define JOYSTICK_CONTROLLER_H

#include <QObject>

class QGamepad;

namespace domain
{
    class JoystickController: public QObject
    {
        Q_OBJECT

    public:
        explicit JoystickController(int device, QObject* parent = nullptr);

        float value(int axis) const;

    signals:
        void valueChanged(int axis, float value);

    private:
        QGamepad* m_gamepad;
    };
}
#endif // JOYSTICK_CONTROLLER_H
