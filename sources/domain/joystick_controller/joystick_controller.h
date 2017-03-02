#ifndef JOYSTICK_CONTROLLER_H
#define JOYSTICK_CONTROLLER_H

#include <QObject>

namespace domain
{
    class JoystickController: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(double axisX READ axisX NOTIFY axisXChanged)
        Q_PROPERTY(double axisY READ axisY NOTIFY axisYChanged)
        Q_PROPERTY(double axisZ READ axisZ NOTIFY axisZChanged)
        Q_PROPERTY(double axisR READ axisR NOTIFY axisRChanged)

    public:
        explicit JoystickController(QObject* parent = nullptr);
        ~JoystickController() override;

        void init();

        double axisX() const;
        double axisY() const;
        double axisZ() const;
        double axisR() const;

    signals:
        void axisXChanged(double axisX);
        void axisYChanged(double axisY);
        void axisZChanged(double axisZ);
        void axisRChanged(double axisR);

    private:
        class Impl;
        Impl* const d;

        Q_DISABLE_COPY(JoystickController)
    };
}

#endif // JOYSTICK_CONTROLLER_H
