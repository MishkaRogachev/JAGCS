#ifndef COMMAND_CONTROLLER_H
#define COMMAND_CONTROLLER_H

// Internal
#include "command.h"

namespace presentation
{
    class CommandController: public QObject
    {
        Q_OBJECT

    public:
        explicit CommandController(QObject* parent = nullptr);
        ~CommandController() override;

    public slots:
        void setControlVehicle(int vehicleId);

        void executeCommand(int commandType, const QVariant& args);
        void rejectCommand(int commandType);

    signals:
        void commandStatusChanged(domain::Command::CommandType type,
                                  domain::Command::CommandStatus status);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_CONTROLLER_H
