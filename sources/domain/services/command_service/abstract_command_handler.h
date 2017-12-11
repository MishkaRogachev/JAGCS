#ifndef ABSTRACT_COMMAND_HANDLER_H
#define ABSTRACT_COMMAND_HANDLER_H

#include <QObject>

// Internal
#include "dao_traits.h"
#include "command.h"

namespace domain
{
    class AbstractCommandHandler: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractCommandHandler(QObject* parent = nullptr);

    protected:
        virtual void sendCommand(int vehicleId,
                                 const dao::CommandPtr& command,
                                 int attempt = 0) = 0;

    signals:
        void ackCommand(int vehicleId,
                        dao::Command::CommandType type,
                        dao::Command::CommandStatus status);
    };
}

#endif // ABSTRACT_COMMAND_HANDLER_H
