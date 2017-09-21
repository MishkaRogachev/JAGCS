#ifndef JOYSTICK_MANAGER_H
#define JOYSTICK_MANAGER_H

#include <QObject>

namespace domain
{
    class JoystickManager : public QObject
    {
        Q_OBJECT

    public:
        explicit JoystickManager(QObject* parent = nullptr);
        ~JoystickManager() override;

        float value(int axis) const;

    public slots:
        void overrideValue(int axis, float value);
        void setControlVehicle(int vehicleId);

    signals:
        void valueChanged(int axis, float value);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // JOYSTICK_MANAGER_H
