#ifndef LOG_BUS_H
#define LOG_BUS_H

// Internal
#include "log_message.h"

// Qt
#include <QMutex>

namespace domain
{
    class LogBus: public QObject
    {
        Q_OBJECT

    public:
        static LogBus* instance();

        static const QList<dto::LogMessage>& logs();

        static void log(const dto::LogMessage& message);
        static void log(const QString& message,
                        dto::LogMessage::LogType type = dto::LogMessage::Common);

    signals:
        void logAdded(dto::LogMessage message);

    private:
        LogBus();

        QList<dto::LogMessage> m_messages;
        QMutex m_mutex;
    };
}

#endif // LOG_BUS_H
