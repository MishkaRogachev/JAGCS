#ifndef MANUAL_CONTROLLER_H
#define MANUAL_CONTROLLER_H

#include <QObject>

namespace domain
{
    class ManualController: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
        Q_PROPERTY(bool joystickEnabled READ joystickEnabled WRITE setJoystickEnabled
                   NOTIFY joystickEnabledChanged)
        Q_PROPERTY(int vehicleId READ vehicleId WRITE setVehicleId NOTIFY vehicleIdChanged)

    public:
        enum Axis {
            NoneAxis,
            Pitch,
            Roll,
            Yaw,
            Throttle
        };

        static const QList<Axis> axes;

        explicit ManualController(QObject* parent = nullptr);
        ~ManualController() override;

        bool enabled() const;
        bool joystickEnabled() const;
        int vehicleId() const;

        Q_INVOKABLE double impact(Axis axis) const;

    public slots:
        void setEnabled(bool enabled);
        void setJoystickEnabled(bool enabled);
        void setJoystickDevice(int deviceId);
        void setVehicleId(int vehicleId);
        void updateJoystickAxes();

        void setImpact(Axis axis, double impact);
        void addImpact(Axis axis, double impact);
        void clearImpacts();
        void sendImpacts();

    signals:
        void enabledChanged(bool enabled);
        void joystickEnabledChanged(bool joystickEnabled);
        void vehicleIdChanged(int vehicleId);

        void impactChanged(Axis axis, double impact);

    private slots:
        void onTimeout();

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        Q_ENUM(Axis)
    };
}

#endif // MANUAL_CONTROLLER_H
