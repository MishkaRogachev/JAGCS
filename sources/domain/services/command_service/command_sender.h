#ifndef COMMAND_SENDER_H
#define COMMAND_SENDER_H

// Internal
#include "command.h"

namespace domain
{
    class CommandSender: public QObject
    {
        Q_OBJECT

    public:
        explicit CommandSender(QObject* parent = nullptr);
        ~CommandSender() override;

    public slots:
        void addCommand(const Command& command);
        void removeCommand(Command::CommandType type);

        void setCommandStatus(Command::CommandType type, Command::CommandStatus status);

    signals:
        void sendCommand(const Command& command, int attempt);
        void commandStatusChanged(Command::CommandType type, Command::CommandStatus status);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_SENDER_H
