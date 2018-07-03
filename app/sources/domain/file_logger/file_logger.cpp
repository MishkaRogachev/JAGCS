#include "file_logger.h"

// Qt
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QApplication>
#include <QDebug>

using namespace domain;

namespace
{
    const QString logs = "logs";
}

FileLogger::FileLogger(QObject* parent):
    QObject(parent),
    m_file(new QFile(::logs + "/" +
                     QDateTime::currentDateTime().toString("yyyy.MM.dd-hh:mm:ss") +
                     ".log"))
{
    QDir dir;
    if (!dir.exists(::logs) && !dir.mkdir(::logs))
    {
        qFatal("Can not create log directory!");
    }

    if (!m_file->open(QIODevice::Append | QIODevice::Text))
    {
        qFatal("Can not open log file!");
    }
}

void FileLogger::log(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QTextStream out(m_file);
    out << QTime::currentTime().toString("hh:mm:ss.zzzz ") <<
           qFormatLogMessage(type, context, msg) << "\n";
    out.flush();
}
