#ifndef COMMAND_SERVICE_H
#define COMMAND_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "command.h"

namespace domain
{
    class CommandService: public QObject
    {
        Q_OBJECT

    public:
        explicit CommandService(QObject* parent = nullptr);
        ~CommandService() override;

    public slots:
        void executeCommand(int vehicleId, const Command& command);
        void rejectCommand(int vehicleId, Command::CommandType type);

    signals:
        void commandStatusChanged(const Command& command);

    private:
        class Impl;
        const QScopedPointer<Impl> d;
    };
}

#endif // COMMAND_SERVICE_H
