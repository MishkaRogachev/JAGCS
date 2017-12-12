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
        ~AbstractCommandHandler() override;

    public slots:
        void executeCommand(int vehicleId, const dao::CommandPtr& command);
        void cancelCommand(int vehicleId, dao::Command::CommandType type);

    signals:
        void commandChanged(dao::CommandPtr command);

    protected:
        void ackCommand(int vehicleId, dao::Command::CommandType type, dao::Command::CommandStatus status);
        void stopCommand(int vehicleId, const dao::CommandPtr& command);
        void timerEvent(QTimerEvent* event) override;

        virtual void sendCommand(int vehicleId, const dao::CommandPtr& command, int attempt = 0) = 0;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // ABSTRACT_COMMAND_HANDLER_H
