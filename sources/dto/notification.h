#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <QTime>

namespace dto
{
    class Notification
    {
        Q_GADGET

        Q_PROPERTY(QTime timestamp READ timestamp WRITE setTimestamp)
        Q_PROPERTY(QString head READ head WRITE setHead)
        Q_PROPERTY(QString message READ message WRITE setMessage)
        Q_PROPERTY(Urgency urgency READ urgency WRITE setUrgency)
        Q_PROPERTY(int time READ time WRITE setTime)

    public:
        enum Urgency
        {
            Common,
            Positive,
            Warning,
            Critical
        };

        Notification(const QTime& timestamp = QTime::currentTime(),
                     const QString& head = QString(),
                     const QString& message = QString(),
                     Urgency urgency = Common,
                     int time = 0);

        QTime timestamp() const;
        void setTimestamp(const QTime& timestamp);

        QString head() const;
        void setHead(const QString& head);

        QString message() const;
        void setMessage(const QString& message);

        Urgency urgency() const;
        void setUrgency(Urgency urgency);

        int time() const;
        void setTime(int time);

        bool operator ==(const Notification& other);

    private:
        QTime m_timestamp;
        QString m_head;
        QString m_message;
        Urgency m_urgency;
        int m_time;

        Q_ENUM(Urgency)
    };
}

#endif // NOTIFICATION_H
