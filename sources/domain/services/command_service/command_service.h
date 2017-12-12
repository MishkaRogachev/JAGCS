#ifndef COMMAND_SERVICE_H
#define COMMAND_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"
#include "command.h"

namespace domain
{
    class AbstractCommandHandler;

    class CommandService: public QObject
    {
        Q_OBJECT

    public:
        explicit CommandService(QObject* parent = nullptr);

    public slots:
        void addHandler(AbstractCommandHandler* handler);
        void removeHandler(AbstractCommandHandler* handler);

    signals:
        void executeCommand(int vehicleId, const dao::CommandPtr& command);
        void cancelCommand(int vehicleId, dao::Command::CommandType type);

        void commandChanged(dao::CommandPtr command);
    };
}

#endif // COMMAND_SERVICE_H
