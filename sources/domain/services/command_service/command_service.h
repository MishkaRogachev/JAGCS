#ifndef COMMAND_SERVICE_H
#define COMMAND_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"
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
        void executeCommand(int vehicleId, const dto::CommandPtr& command);
        void cancelCommand(int vehicleId, dto::Command::CommandType type);

        void commandChanged(dto::CommandPtr command);
    };
}

#endif // COMMAND_SERVICE_H
