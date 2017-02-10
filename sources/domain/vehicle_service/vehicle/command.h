#ifndef COMMAND_H
#define COMMAND_H

namespace domain
{
    enum class Command
    {
        UnknownCommand = 0,
        Home,
        Takeoff,
        Waypoint,
        LoiterAltitude,
        LoiterTurns,
        Continue,
        Return,
        Landing
    };
}

#endif // COMMAND_H
