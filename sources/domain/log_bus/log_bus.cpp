#include "log_bus.h"

// Qt
#include <QDebug>

using namespace domain;

class LogBus::Impl
{
public:
    QList<LogMessage> m_messages;
};

LogBus::~LogBus()
{}

LogBus* LogBus::instance()
{
    static LogBus bus;
    return &bus;
}

QList<LogMessage> LogBus::messages()
{
    return instance()->d->m_messages;
}

void LogBus::addLogMessage(const LogMessage& message)
{
    instance()->d->m_messages.append(message);
    emit instance()->newMessage(message);
}

LogBus::LogBus()
{}
