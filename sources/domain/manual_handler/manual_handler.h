#ifndef MANUAL_HANDLER_H
#define MANUAL_HANDLER_H

#include <QObject>

namespace domain
{
    class ManualHandler: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
        Q_PROPERTY(bool joystickEnabled READ joystickEnabled NOTIFY joystickEnabledChanged)
        Q_PROPERTY(int vehicleId READ vehicleId WRITE setVehicleId NOTIFY vehicleIdChanged)

    public:
        enum Axis {
            NoneAxis,
            Pitch,
            Roll,
            Yaw,
            Throttle
        };

        explicit ManualHandler(QObject* parent = nullptr);
        ~ManualHandler() override;

        bool enabled() const;
        bool joystickEnabled() const;
        int vehicleId() const;

        float impact(Axis axis) const;

    public slots:
        void setEnabled(bool enabled);
        void setJoystick(int deviceId);
        void setVehicleId(int vehicleId);
        void updateJoystickAxes();

        void setImpact(Axis axis, float impact);
        void sendImpacts();

    signals:
        void enabledChanged(bool enabled);
        void joystickEnabledChanged(bool joystickEnabled);
        void vehicleIdChanged(int vehicleId);

        void impactChanged(Axis axis, float impact);

    private slots:
        void onControllerValueChanged(int axis, float value);

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        Q_ENUM(Axis)
    };
}

#endif // MANUAL_HANDLER_H
