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

        static const QList<LogMessage>& logs();

        static void log(const LogMessage& message);
        static void log(const QString& message, LogMessage::LogType type = LogMessage::Common);

    signals:
        void logAdded(LogMessage message);

    private:
        LogBus();

        QList<LogMessage> m_messages;
        QMutex m_mutex;
    };
}

#endif // LOG_BUS_H
