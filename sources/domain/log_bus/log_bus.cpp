#include "log_bus.h"

// Qt
#include <QDebug>

using namespace domain;

LogBus* LogBus::instance()
{
    static LogBus bus;
    return &bus;
}

QList<LogMessage> LogBus::logs()
{
    return instance()->m_messages;
}

void LogBus::log(const LogMessage& message)
{
    instance()->m_messages.append(message);
    emit instance()->logAdded(message);
}

void LogBus::log(const QString& message, LogMessage::LogType type)
{
    LogBus::log(LogMessage(QTime::currentTime(), message, type));
}

LogBus::LogBus()
{}
