#ifndef COMMAND_SENDER_H
#define COMMAND_SENDER_H

// Internal
#include "dao_traits.h"
#include "command.h"

namespace domain
{
    class CommandSender: public QObject
    {
        Q_OBJECT

    public:
        explicit CommandSender(QObject* parent = nullptr);
        ~CommandSender() override;

        bool hasCommand(dao::Command::CommandType type) const;
        dao::CommandPtr takeCommand(dao::Command::CommandType type);

    public slots:
        void addCommand(const dao::CommandPtr& command);
        void finishCommand(dao::Command::CommandType type, dao::Command::CommandStatus status);

    signals:
        void sendCommand(dao::CommandPtr command, int attempt);
        void commandChanged(dao::CommandPtr command);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_SENDER_H
