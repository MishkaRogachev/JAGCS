#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include "command.h"

namespace data_source
{
    class MissionItem
    {
    public:
        MissionItem();

        domain::Command command() const;
        void setCommand(const domain::Command& command);

    private:
        domain::Command m_command;
    };
}

#endif // MISSION_ITEM_H
