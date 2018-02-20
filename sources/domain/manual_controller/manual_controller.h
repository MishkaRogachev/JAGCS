#ifndef MANUAL_CONTROLLER_H
#define MANUAL_CONTROLLER_H

#include <QObject>

namespace domain
{
    class ManualController: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)

    public:
        enum Axis {
            Pitch,
            Roll,
            Yaw,
            Throttle
        };

        explicit ManualController(QObject* parent = nullptr);
        ~ManualController() override;

        bool enabled() const;

    public slots:
        void setEnabled(bool enabled);
        void sentImpact(Axis axis, float impact);
        void sendImpacts();

    signals:
        void enabledChanged(bool enabled);

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        Q_ENUM(Axis)
    };
}

#endif // MANUAL_CONTROLLER_H
