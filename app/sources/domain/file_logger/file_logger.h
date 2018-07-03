#ifndef APP_FILE_LOGGER_H
#define APP_FILE_LOGGER_H

// Qt
#include <QObject>

class QFile;

namespace domain
{
    class FileLogger: public QObject
    {
        Q_OBJECT

    public:
        explicit FileLogger(QObject* parent = nullptr);

    public slots:
        void log(QtMsgType type, const QMessageLogContext& context, const QString& msg);

    private:
        QFile* m_file;
    };

    inline void log(QtMsgType type, const QMessageLogContext& context, const QString& msg)
    {
        static FileLogger logger;
        logger.log(type, context, msg);
    }
}

#endif // APP_FILE_LOGGER_H
