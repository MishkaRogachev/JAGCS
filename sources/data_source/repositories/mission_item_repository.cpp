#include "mission_item_repository.h"

using namespace data_source;

MissionItemRepository::MissionItemRepository():
    GenericRepository()
{}

QList<MissionItem*> MissionItemRepository::selectMissionItems(int missionId)
{
    return this->select(QString("missionId = %1").arg(missionId));
}
