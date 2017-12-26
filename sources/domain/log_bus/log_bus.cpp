#include "log_bus.h"

// Qt
#include <QMutexLocker>
#include <QDebug>

using namespace domain;

LogBus* LogBus::instance()
{
    static LogBus bus;
    return &bus;
}

const QList<LogMessage>& LogBus::logs()
{
    QMutexLocker locker(&instance()->m_mutex);
    return instance()->m_messages;
}

void LogBus::log(const LogMessage& message)
{
    QMutexLocker locker(&instance()->m_mutex);
    instance()->m_messages.append(message);
    emit instance()->logAdded(message);
}

void LogBus::log(const QString& message, LogMessage::LogType type)
{
    LogBus::log(LogMessage(QTime::currentTime(), message, type));
}

LogBus::LogBus():
    m_mutex(QMutex::Recursive)
{
    qRegisterMetaType<LogMessage>("LogMessage");
}
