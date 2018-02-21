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
        explicit JoystickController(QObject* parent = nullptr);

        float value(int axis) const;
        int deviceId() const;

    public slots:
        void setDeviceId(int deviceId);

    signals:
        void valueChanged(int axis, float value);

    private:
        QGamepad* m_gamepad;
    };
}
#endif // JOYSTICK_CONTROLLER_H
