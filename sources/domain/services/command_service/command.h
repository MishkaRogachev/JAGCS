#ifndef COMMAND_H
#define COMMAND_H

// Qt
#include <QObject>
#include <QVariant>

namespace domain
{
    class Command
    {
        Q_GADGET

    public:
        // TODO: Merge command and mission item comman enums
        enum CommandType
        {
            UnknownCommand,

            SetMode,
            GoToItem,
            NavTo,

            ArmDisarm,

            Return,
            Start,
            Land,
            GoAround,
            PauseContinue,

            Parachute,

            SetSpeed, //TODO: separate throttle, airspeed and groundspeed commands
            SetAltitude,
            SetHome,

            PreflightCalibration
        };

        enum CommandStatus
        {
            Idle,
            Rejected,
            Canceled,
            Sending,
            InProgress,
            Completed,
        };

        Command(CommandType type = UnknownCommand, CommandStatus status = Idle);
        Command(const Command& command);

        CommandType type() const;
        void setType(CommandType type);

        CommandStatus status() const;
        void setStatus(CommandStatus status);

        QVariantList arguments() const;
        void setArguments(const QVariantList& arguments);
        void addArgument(const QVariant& argument);

    private:
        CommandType m_type;
        CommandStatus m_status;
        QVariantList m_arguments;

        Q_ENUM(CommandType)
        Q_ENUM(CommandStatus)
    };
}

#endif // COMMAND_H
