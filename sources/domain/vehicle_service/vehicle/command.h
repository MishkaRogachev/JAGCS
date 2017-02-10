#ifndef COMMAND_H
#define COMMAND_H

namespace domain
{
    enum class Command
    {
        UnknownCommand = 0,
// Mission commands
        Home,
        Takeoff,
        Waypoint,
        LoiterAltitude,
        LoiterTurns,
        Continue,
        Return,
        Landing,
// Control commands
        Arm,
        Disarm
    };
}

#endif // COMMAND_H
