#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include "command.h"

namespace data_source
{
    class MissionItem
    {
    public:
        MissionItem(int id, domain::Command command = domain::Command::UnknownCommand);

        int id() const;

        domain::Command command() const;
        void setCommand(domain::Command command);

    private:
        const int m_id;
        domain::Command m_command;
    };
}

#endif // MISSION_ITEM_H
