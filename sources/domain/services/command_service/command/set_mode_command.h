#ifndef SET_MODE_COMMAND_H
#define SET_MODE_COMMAND_H

#include "command.h"

namespace domain
{
    class SetModeCommand : public Command
    {
        Q_GADGET

    public:
        enum Mode // TODO: command global enums(Commands, Telemetry, Parameters, Devices)
        {
            UnknownMode,

            Auto,
            Loiter,
            Guided
        };

        SetModeCommand(int vehicleId);

        Mode mode() const;
        void setMode(Mode mode);

    private:
        Q_ENUM(Mode)
    };
}

#endif // SET_MODE_COMMAND_H
