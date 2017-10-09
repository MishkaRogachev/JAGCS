#include "set_mode_command.h"

using namespace domain;

SetModeCommand::SetModeCommand(int vehicleId):
    Command(Command::SetMode, vehicleId)
{}

SetModeCommand::Mode SetModeCommand::mode() const
{
    if (this->arguments().count() > 0) return this->arguments().first().value<Mode>();

    return UnknownMode;
}

void SetModeCommand::setMode(SetModeCommand::Mode mode)
{
    QVariantList args;
    args.append(QVariant::fromValue(mode));
    this->setArguments(args);
}
