#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include "persistable.h"
#include "command.h"

namespace data_source
{
    class MissionItem: public Persistable
    {
    public:
        MissionItem();
        //bool save() override;

        domain::Command command() const;
        void setCommand(const domain::Command& command);

    protected:
        const char* tableName() const override;
        const char* tableParams() const override;
        QString params() const override;

    private:
        domain::Command m_command;
    };
}

#endif // MISSION_ITEM_H
