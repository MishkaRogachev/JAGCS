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

        void rejectCommand(Command::CommandType type);
        void confirmCommand(Command::CommandType type);

    signals:
        void sendCommand(const Command& command, int attempt);

        void commandCompleted(Command::CommandType type);
        void commandRejected(Command::CommandType type);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_SENDER_H
