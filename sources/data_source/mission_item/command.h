#ifndef COMMAND_H
#define COMMAND_H

namespace data_source
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
        Landing,
    };
}

#endif // COMMAND_H
