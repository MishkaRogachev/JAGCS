#ifndef STATUS_H
#define STATUS_H

#include <QObject>

namespace domain
{
    class Status
    {
        Q_GADGET

    public:
        Status(bool armed = false, bool online = false,
               const QString& modeString = QString());

        bool armed() const;
        void setArmed(bool armed);

        bool online() const;
        void setOnline(bool online);

        QString modeString() const;
        void setModeString(const QString& modeString);

         bool operator ==(const Status& other);

    private:
        bool m_armed;
        bool m_online;
        QString m_modeString;
    };
}

#endif // STATUS_H
