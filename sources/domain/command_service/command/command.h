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
            Idle,

            ArmDisarm,

            Return,
            Start,
            Jump,

            Parachute
        };

        Command(CommandType type, int vehicleId);

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
    };
}

#endif // COMMAND_H
