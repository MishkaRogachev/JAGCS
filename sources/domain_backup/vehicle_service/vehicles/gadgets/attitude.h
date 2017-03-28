#ifndef ATTITUDE_H
#define ATTITUDE_H

#include <QObject>

namespace domain
{
    class Attitude
    {
        Q_GADGET

        Q_PROPERTY(float pitch READ pitch CONSTANT)
        Q_PROPERTY(float roll READ roll CONSTANT)
        Q_PROPERTY(float yaw READ yaw CONSTANT)

    public:
        Attitude(float pitch = 0.0, float roll = 0.0, float yaw = 0.0);

        float pitch() const;
        float roll() const;
        float yaw() const;

        bool operator ==(const Attitude& other);

    private:
        float m_pitch;
        float m_roll;
        float m_yaw;
    };
}

#endif // ATTITUDE_H
