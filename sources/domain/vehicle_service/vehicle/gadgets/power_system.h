#ifndef POWER_SYSTEM_H
#define POWER_SYSTEM_H

// Qt
#include <QObject>

namespace domain
{
    class PowerSystem
    {
        Q_GADGET

        Q_PROPERTY(float voltage READ voltage CONSTANT)
        Q_PROPERTY(float current READ current CONSTANT)
        Q_PROPERTY(int charge READ charge CONSTANT)

    public:
        PowerSystem(float voltage = 0.0, float current = 0.0,
                    int charge = 100);

        float voltage() const;
        float current() const;
        int charge() const;

        bool operator ==(const PowerSystem& other);

    private:
        float m_voltage;
        float m_current;
        int m_charge;
    };
}

#endif // POWER_SYSTEM_H
