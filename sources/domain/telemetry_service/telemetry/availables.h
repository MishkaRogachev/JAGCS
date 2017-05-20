#ifndef AVAILABLES_H
#define AVAILABLES_H

// Qt
#include <QObject>

namespace domain
{
    class Availables
    {
        Q_GADGET

    public:
        Availables(bool ahrsAvailable = false,
                   bool insAvailable = false,
                   bool snsAvailable = false,
                   bool compasAvailable = false,
                   bool airSpeedAvailable = false,
                   bool barometerAvailable = false,
                   bool rangeFinderAvailable = false);

        bool ahrsAvailable() const;
        bool insAvailable() const;
        bool snsAvailable() const;
        bool compasAvailable() const;
        bool airSpeedAvailable() const;
        bool barometerAvailable() const;
        bool rangeFinderAvailable() const;

        bool operator ==(const Availables& other);

    private:
        bool m_ahrsAvailable;
        bool m_insAvailable;
        bool m_snsAvailable;
        bool m_compasAvailable;
        bool m_airSpeedAvailable;
        bool m_barometerAvailable;
        bool m_rangeFinderAvailable;
    };
}

#endif // AVAILABLES_H
