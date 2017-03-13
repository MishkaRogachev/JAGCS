#include "mission_item.h"

using namespace data_source;

MissionItem::MissionItem():
    Persistable()
{}

QString MissionItem::tableName() const
{
    return "mission_items";
}
