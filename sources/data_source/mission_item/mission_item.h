#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include "command.h"

namespace data_source
{
    class MissionItem
    {
    public:
        MissionItem(int id, Command command = Command::UnknownCommand);

        int id() const;

        Command command() const;
        void setCommand(Command command);

    private:
        const int m_id;
        Command m_command;
    };
}

#endif // MISSION_ITEM_H
