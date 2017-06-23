#ifndef COMMAND_H
#define COMMAND_H

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
            Jump
        };

        Command(CommandType type);

        CommandType type() const;
        void setType(CommandType type);

        QVariantList arguments() const;
        void setArguments(const QVariantList& arguments);

    private:
        CommandType m_type;
        QVariantList m_arguments;

        Q_ENUM(CommandType)
    };
}

#endif // COMMAND_H
