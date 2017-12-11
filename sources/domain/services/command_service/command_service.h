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
        ~CommandService() override;

        void addHandler(AbstractCommandHandler* handler);

    public slots:
        void executeCommand(int vehicleId, const dao::CommandPtr& command);
        void cancelCommand(int vehicleId, dao::Command::CommandType type);

    signals:
        void commandChanged(dao::CommandPtr command);

    private:
        class Impl;
        const QScopedPointer<Impl> d;
    };
}

#endif // COMMAND_SERVICE_H
