#ifndef ABSTRACT_COMMAND_HANDLER_H
#define ABSTRACT_COMMAND_HANDLER_H

#include <QObject>

// Internal
#include "dto_traits.h"
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
        void executeCommand(int vehicleId, const dto::CommandPtr& command);
        void cancelCommand(int vehicleId, dto::Command::CommandType type);

    signals:
        void commandChanged(dto::CommandPtr command);

    protected:
        void ackCommand(int vehicleId, dto::Command::CommandType type, dto::Command::CommandStatus status);
        void stopCommand(int vehicleId, const dto::CommandPtr& command);
        void timerEvent(QTimerEvent* event) override;

        virtual void sendCommand(int vehicleId, const dto::CommandPtr& command, int attempt = 0) = 0;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // ABSTRACT_COMMAND_HANDLER_H
