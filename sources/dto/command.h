#ifndef COMMAND_H
#define COMMAND_H

// Internal
#include "base_dto.h"

// Qt
#include <QVariant>

namespace dto
{
    class Command: public BaseDto
    {
        Q_GADGET

        Q_PROPERTY(CommandType type READ type WRITE setType)
        Q_PROPERTY(CommandStatus status READ status WRITE setStatus)
        Q_PROPERTY(QVariantList arguments READ arguments WRITE setArguments)

    public:
        // TODO: Merge command and mission item comman enums
        enum CommandType
        {
            UnknownCommand,

            ArmDisarm,

            SetMode,

            Return,
            Start,
            Land,
            GoAround,
            PauseContinue,

            GoTo,
            NavTo,

            ChangeAltitude,
            SetAirspeed,
            SetGroundspeed,
            SetThrottle,

            ManualImpacts,

            Parachute,

            SetReturn,

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

        CommandType type() const;
        void setType(CommandType type);

        CommandStatus status() const;
        void setStatus(CommandStatus status);

        QVariantList arguments() const;
        void setArguments(const QVariantList& arguments);
        void addArgument(const QVariant& argument);

        bool isFinished() const;

    private:
        CommandType m_type = UnknownCommand;
        CommandStatus m_status = Idle;
        QVariantList m_arguments;

        Q_ENUM(CommandType)
        Q_ENUM(CommandStatus)
    };
}

#endif // COMMAND_H
