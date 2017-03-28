#include "return_mission_item.h"

using namespace domain;

ReturnMissionItem::ReturnMissionItem(Mission* mission):
    AbstractMissionItem(mission, Command::Return)
{}

void ReturnMissionItem::clone(AbstractMissionItem* mission)
{
    Q_UNUSED(mission)
}
