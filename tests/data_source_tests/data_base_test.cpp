#include "data_base_test.h"

// Qt
#include <QDebug>

// Internal
#include "identity_map.h"

#include "mission.h"
#include "mission_item.h"

using namespace data_source;

void DataBaseTest::testMissionCrud()
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

void DataBaseTest::testMissionItemCrud()
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

    mission = iMap.mission(mission->id());
    iMap.removeMission(mission);
}

void DataBaseTest::testMissionItemsInMission()
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

    iMap.saveMissionAll(mission);
    iMap.unloadMission(mission);
    QCOMPARE(iMap.mission(mission->id())->items().count(), 15);

    mission = iMap.mission(mission->id());

    iMap.removeMissionItem(mission->items().takeAt(3));

    QCOMPARE(mission->items().count(), 14);
    iMap.unloadMission(mission);
    QCOMPARE(iMap.mission(mission->id())->items().count(), 14);

    QCOMPARE(mission->item(0)->periods(), 0);
    QCOMPARE(mission->item(1)->periods(), 1);
    QCOMPARE(mission->item(2)->periods(), 2);
    QCOMPARE(mission->item(3)->periods(), 4);

    mission = iMap.mission(mission->id());
    iMap.removeMission(mission);
}

void DataBaseTest::testMissionItemSequence()
{
    IdentityMap iMap;

    MissionPtr mission = iMap.createMission();

    for (int i = 0; i < 25; ++i) iMap.createItemForMission(mission);

    iMap.unloadMission(mission);
    mission = iMap.mission(mission->id());

    for (int i = 0; i < 25; ++i) QCOMPARE(i, mission->item(i)->sequence());

    iMap.removeMissionItem(mission->takeItem(5));
    iMap.removeMissionItem(mission->takeItem(7));
    iMap.removeMissionItem(mission->takeItem(8));

    for (int i = 0; i < 22; ++i) QCOMPARE(i, mission->item(i)->sequence());

    iMap.saveMissionAll(mission);
    iMap.unloadMission(mission);
    mission = iMap.mission(mission->id());

    for (int i = 0; i < 22; ++i) QCOMPARE(i, mission->item(i)->sequence());

    mission = iMap.mission(mission->id());
    iMap.removeMission(mission);
}

void DataBaseTest::testMissionItemUpDown()
{
    IdentityMap iMap;

    MissionPtr mission = iMap.createMission();

    for (int i = 0; i < 10; ++i)
    {
        MissionItemPtr item = iMap.createItemForMission(mission);
        item->setPeriods(i);
    }

    QCOMPARE(mission->item(0)->periods(), 0);
    QCOMPARE(mission->item(9)->periods(), 9);

    mission->insertItem(0, mission->takeItem(9));

    QCOMPARE(mission->item(0)->periods(), 9);
    QCOMPARE(mission->item(9)->periods(), 8);

    mission->insertItem(9, mission->takeItem(1));

    QCOMPARE(mission->item(1)->periods(), 1);
    QCOMPARE(mission->item(9)->periods(), 0);

    QCOMPARE(mission->item(3)->periods(), 3);
    QCOMPARE(mission->item(4)->periods(), 4);

    mission->item(3)->up();

    QCOMPARE(mission->item(4)->periods(), 3);
    QCOMPARE(mission->item(3)->periods(), 4);

    QCOMPARE(mission->item(7)->periods(), 7);
    QCOMPARE(mission->item(6)->periods(), 6);

    mission->item(7)->down();

    QCOMPARE(mission->item(7)->periods(), 6);
    QCOMPARE(mission->item(6)->periods(), 7);

    iMap.removeMission(mission);
}
