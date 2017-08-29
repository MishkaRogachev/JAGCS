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
        ~LogBus() override;
        static LogBus* instance();

        static QList<LogMessage> messages();

        static void addLogMessage(const LogMessage& message);

    signals:
        void newMessage(LogMessage message);

    private:
        LogBus();

        class Impl;
        QScopedPointer<Impl> const d;
        Q_DISABLE_COPY(LogBus)
    };
}

#endif // LOG_BUS_H
