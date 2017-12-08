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

        bool hasCommand(Command::CommandType type) const;
        Command takeCommand(Command::CommandType type);

    public slots:
        void addCommand(const Command& command);
        void finishCommand(Command::CommandType type, Command::CommandStatus status);

    signals:
        void sendCommand(const Command& command, int attempt);
        void commandFinished(const Command& command);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_SENDER_H
