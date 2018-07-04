#ifndef SATELLITE_INFO_H
#define SATELLITE_INFO_H

#include <QObject>

namespace domain
{
    struct SatelliteInfo
    {
        Q_GADGET

        Q_PROPERTY(quint8 prn READ prn WRITE setPrn)
        Q_PROPERTY(bool used READ used WRITE setUsed)
        Q_PROPERTY(quint8 elevation READ elevation WRITE setElevation)
        Q_PROPERTY(quint8 azimuth READ azimuth WRITE setAzimuth)
        Q_PROPERTY(quint8 snr READ snr WRITE setSnr)

    public:
        SatelliteInfo(quint8 prn = 0, bool used = false, quint8 elevation = 0,
                      quint8 azimuth = 0, quint8 snr = 0);

        quint8 prn() const;
        bool used() const;
        quint8 elevation() const;
        quint8 azimuth() const;
        quint8 snr() const;

    public slots:
        void setPrn(quint8 prn);
        void setUsed(bool used);
        void setElevation(quint8 elevation);
        void setAzimuth(quint8 azimuth);
        void setSnr(quint8 snr);

    private:
        quint8 m_prn;
        bool m_used;
        quint8 m_elevation;
        quint8 m_azimuth;
        quint8 m_snr;
    };
}

#endif // SATELLITE_INFO_H
