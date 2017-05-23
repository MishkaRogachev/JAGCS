#ifndef STATUS_H
#define STATUS_H

#include <QObject>

namespace domain
{
    class Status
    {
        Q_GADGET

    public:
        Status(bool armed = false, const QString& modeString = QString());

        bool armed() const;
        QString modeString() const;

        bool operator ==(const Status& other);

    private:
        bool m_armed;
        QString m_modeString;
    };
}

#endif // STATUS_H
