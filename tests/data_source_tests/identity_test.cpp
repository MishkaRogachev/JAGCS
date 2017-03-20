#include "identity_test.h"

// Qt
#include <QDebug>

// Internal
#include "identity_map.h"

#include "mission.h"
#include "mission_item.h"

using namespace data_source;

void IdentityTest::testMissionIdentity()
{
    IdentityMap map;

    MissionPtr mission = map.createMission();

    QCOMPARE(mission->id(), map.mission(mission->id())->id());
    QCOMPARE(mission.data(), map.mission(mission->id()).data());

    mission->setName("Some ridiculous name");

    QCOMPARE(mission->name(), map.mission(mission->id())->name());

    map.saveMission(mission);

    map.clear();

    QCOMPARE(mission->name(), map.mission(mission->id())->name());
}

void IdentityTest::testMissionItemIdentity()
{
    IdentityMap map;

    MissionPtr mission = map.createMission();
    MissionItemPtr missionItem = map.createMissionItem(mission);

    QCOMPARE(missionItem->missionId(), mission->id());
    QCOMPARE(missionItem->id(), map.missionItem(missionItem->id())->id());
    QCOMPARE(missionItem.data(), map.missionItem(missionItem->id()).data());

    missionItem->setCommand(MissionItem::Waypoint);

    QCOMPARE(missionItem->command(), map.missionItem(missionItem->id())->command());

    map.saveMissionItem(missionItem);

    map.clear();

    QCOMPARE(missionItem->command(), map.missionItem(missionItem->id())->command());
}
