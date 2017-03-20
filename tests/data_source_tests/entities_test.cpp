#include "entities_test.h"

// Qt
#include <QDebug>

// Internal
#include "identity_map.h"

#include "mission.h"
#include "mission_item.h"

using namespace data_source;

void EntitiesTest::testMissionCrud()
{
    IdentityMap iMap;

    MissionPtr mission = iMap.createMission();

    QVERIFY(mission);

    mission->setName("Some ridiculous name");

    QCOMPARE(mission->name(), iMap.mission(mission->id())->name());
    QCOMPARE(mission, iMap.mission(mission->id()));

    iMap.saveMission(mission);
    iMap.unloadMission(mission);

    QCOMPARE(mission->name(), iMap.mission(mission->id())->name());
    QVERIFY(mission != iMap.mission(mission->id()));

    iMap.removeMission(mission);

    QVERIFY(iMap.mission(mission->id()).isNull());
}

void EntitiesTest::testMissionItemCrud()
{
    IdentityMap iMap;

    MissionPtr mission = iMap.createMission();
    MissionItemPtr item = iMap.createItemForMission(mission);

    QVERIFY(item);
    QCOMPARE(item->mission(), mission);
    QCOMPARE(item, iMap.missionItem(item->id()));

    item->setCommand(MissionItem::Landing);
    item->setLatitude(45.6711);
    item->setLongitude(37.4869);
    item->setAltitude(350.75);

    iMap.saveMissionItem(item);
    iMap.unloadMissionItem(item);

    QCOMPARE(item->mission()->id(), iMap.missionItem(item->id())->mission()->id());
    QCOMPARE(item->mission(), iMap.missionItem(item->id())->mission());
    QVERIFY(qFuzzyCompare(item->latitude(), iMap.missionItem(item->id())->latitude()));
    QVERIFY(qFuzzyCompare(item->longitude(), iMap.missionItem(item->id())->longitude()));
    QVERIFY(qFuzzyCompare(item->altitude(), iMap.missionItem(item->id())->altitude()));
}

void EntitiesTest::testItemsInMission()
{
    IdentityMap iMap;

    MissionPtr mission = iMap.createMission();

    for (int i = 0; i < 15; ++i)
    {
        MissionItemPtr item = iMap.createItemForMission(mission);
        item->setPeriods(i);
    }

    QCOMPARE(mission->items().count(), 15);
    QCOMPARE(iMap.mission(mission->id())->items().count(), 15);

    iMap.unloadMission(mission);
    QCOMPARE(iMap.mission(mission->id())->items().count(), 15);

    mission = iMap.mission(mission->id());

    iMap.removeMissionItem(mission->items().takeAt(3));

    QCOMPARE(mission->items().count(), 14);
    iMap.unloadMission(mission);
    QCOMPARE(iMap.mission(mission->id())->items().count(), 14);
}
