#ifndef LOG_BUS_H
#define LOG_BUS_H

// Internal
#include "log_message.h"

namespace domain
{
    class LogBus: public QObject
    {
        Q_OBJECT

    public:
        static LogBus* instance();

        static QList<LogMessage> logs();

        static void log(const LogMessage& message);
        static void log(const QString& message, LogMessage::LogType type = LogMessage::Common);

    signals:
        void logAdded(LogMessage message);

    private:
        LogBus();

        QList<LogMessage> m_messages;
    };
}

#endif // LOG_BUS_H
