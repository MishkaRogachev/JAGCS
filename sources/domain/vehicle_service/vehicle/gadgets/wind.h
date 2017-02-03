#ifndef WIND_H
#define WIND_H

#include <QObject>

namespace domain
{
    class Wind
    {
        Q_GADGET

        Q_PROPERTY(float direction READ direction CONSTANT)
        Q_PROPERTY(float speed READ speed CONSTANT)
        Q_PROPERTY(float verticalSpeed READ verticalSpeed CONSTANT)

    public:
        Wind(float direction = 0.0, float speed = 0.0, float verticalSpeed = 0.0);

        float direction() const;
        float speed() const;
        float verticalSpeed() const;

        bool operator ==(const Wind& other);

    private:
        float m_direction;
        float m_speed;
        float m_verticalSpeed;
    };
}

#endif // WIND_H
