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
        enum CommandType
        {
            UnknownCommand,

            SetMode,
            SetCurrentItem,

            ArmDisarm,

            Return,
            EnableGuided,
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

        Command(CommandType type = UnknownCommand, int vehicleId = 0);
        Command(const Command& command);

        CommandType type() const;
        void setType(CommandType type);

        QVariantList arguments() const;
        void setArguments(const QVariantList& arguments);
        void addArgument(const QVariant& argument);

        int vehicleId() const;
        void setVehicleId(int vehicleId);

    private:
        CommandType m_type;
        QVariantList m_arguments;
        int m_vehicleId;

        Q_ENUM(CommandType)
        Q_ENUM(CommandStatus)
    };
}

#endif // COMMAND_H
