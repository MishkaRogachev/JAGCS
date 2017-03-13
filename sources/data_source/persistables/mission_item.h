#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include "persistable.h"

namespace data_source
{
    class MissionItem: public Persistable
    {
    public:
        MissionItem();
        //bool save() override;

    protected:
        QString tableName() const override;
    };
}

#endif // MISSION_ITEM_H
