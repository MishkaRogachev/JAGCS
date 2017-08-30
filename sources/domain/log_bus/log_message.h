#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <QObject>
#include <QTime>

namespace domain
{
    class LogMessage
    {
        Q_GADGET

        Q_PROPERTY(QTime timestamp READ timestamp WRITE setTimestamp)
        Q_PROPERTY(QString message READ message WRITE setMessage)
        Q_PROPERTY(LogType type READ type WRITE setType)

    public:
        enum LogType
        {
            Common,
            Positive,
            Warning,
            Critical
        };

        LogMessage(const QTime& timestamp = QTime(),
                   const QString& message = QString(),
                   LogType type = Common);

        QTime timestamp() const;
        void setTimestamp(const QTime& timestamp);

        QString message() const;
        void setMessage(const QString& message);

        LogType type() const;
        void setType(LogType type);

    private:
        QTime m_timestamp;
        QString m_message;
        LogType m_type;

        Q_ENUM(LogType)
    };
}

Q_DECLARE_METATYPE(domain::LogMessage)

#endif // LOG_MESSAGE_H
