#include "data_base_test.h"

// Qt
#include <QDebug>

// Internal
#include "identity_map.h"

#include "mission.h"
#include "mission_item.h"
#include "vehicle.h"

using namespace data_source;

IdentityMap iMap;

void DataBaseTest::testMission()
{
    IdentityMap iMap;

    MissionPtr mission = MissionPtr::create();
    mission->setName("Some ridiculous name");

    QVERIFY2(iMap.saveMission(mission), "Can't insert mission");
    int id = mission->id();
    QVERIFY2(id > 0, "Mission id after insert mus be > 0");

    mission->setName("Another ridiculous name");

    QVERIFY2(iMap.saveMission(mission), "Can't update mission");

    QCOMPARE(mission, iMap.readMission(id));

    mission->setName("Reload will erase this ridiculous name");

    QCOMPARE(mission, iMap.readMission(id, true)); // But pointer will be the same

    QCOMPARE(mission->name(), QString("Another ridiculous name"));

    QVERIFY2(iMap.removeMission(mission), "Can't remove mission");
    QCOMPARE(mission->id(), 0); // Mission id must be zero after remove
}

void DataBaseTest::testMissionItems()
{
    IdentityMap iMap;

    MissionPtr mission = MissionPtr::create();
    mission->setName("Items Mission");
    iMap.saveMission(mission);

    MissionItemPtr item = MissionItemPtr::create();

    item->setCommand(MissionItem::Takeoff);
    item->setLatitude(45.6711);
    item->setLongitude(37.4869);
    item->setAltitude(350.75);
    mission->appendItem(item);

    item = MissionItemPtr::create();

    item->setCommand(MissionItem::Waypoint);
    item->setLatitude(45.3923);
    item->setLongitude(37.6241);
    item->setAltitude(423.17);
    mission->appendItem(item);

    QVERIFY2(iMap.saveMission(mission), "Can't insert mission with items");

    iMap.readMission(mission->id(), true); // reload mission

    QCOMPARE(mission->items().count(), 2);

    item = MissionItemPtr::create();

    item->setCommand(MissionItem::Waypoint);
    item->setLatitude(45.3977);
    item->setLongitude(37.6513);
    item->setAltitude(474.44);

    mission->setItem(3, item);

    QCOMPARE(mission->items().count(), 4);
    QCOMPARE(mission->item(2)->command(), MissionItem::UnknownCommand);
    QVERIFY2(iMap.saveMission(mission), "Can't save mission with items");

    QVERIFY2(item->id(), "Id must be setted on insert");

    QVERIFY2(iMap.removeMission(mission), "Can't remove mission");
    QCOMPARE(item->id(), 0); // Item id must be zero after remove
}

void DataBaseTest::testMissionItemSequence()
{
    IdentityMap iMap;

    MissionPtr mission = MissionPtr::create();

    MissionItemPtr item;
    for (int i = 0; i < 15; ++i)
    {
        item = MissionItemPtr::create();;
        item->setCommand(MissionItem::LoiterTurns);
        item->setPeriods(i);
        mission->appendItem(item);
    }

    QVERIFY2(iMap.saveMission(mission), "Can't save mission with 15 items");
}

/*
void DataBaseTest::testMissionItemsInMission()
{
    IdentityMap iMap;

    MissionPtr mission = iMap.createMission();

    for (int i = 0; i < 15; ++i)
    {
        MissionItemPtr item = iMap.createMissionItem(mission);
        mission->appendItem(item);
        item->setPeriods(i);
    }

    QCOMPARE(mission->items().count(), 15);
    QCOMPARE(iMap.mission(mission->id())->items().count(), 15);

    iMap.saveMission(mission);
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

    for (int i = 0; i < 25; ++i)
    {
        MissionItemPtr missionItem = iMap.createMissionItem(mission);
        mission->appendItem(missionItem);
    }

    iMap.unloadMission(mission);
    mission = iMap.mission(mission->id());

    for (int i = 0; i < 25; ++i) QCOMPARE(i, mission->item(i)->sequence());

    iMap.removeMissionItem(mission->takeItem(5));
    iMap.removeMissionItem(mission->takeItem(7));
    iMap.removeMissionItem(mission->takeItem(8));

    for (int i = 0; i < 22; ++i) QCOMPARE(i, mission->item(i)->sequence());

    iMap.saveMission(mission);
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
        MissionItemPtr item = iMap.createMissionItem(mission);
        mission->appendItem(item);
        item->setPeriods(i);
    }

    QCOMPARE(mission->item(0)->periods(), 0);
    QCOMPARE(mission->item(0)->sequence(), 0);
    QCOMPARE(mission->item(9)->periods(), 9);
    QCOMPARE(mission->item(9)->sequence(), 9);

    mission->insertItem(0, mission->takeItem(9));

    QCOMPARE(mission->item(0)->periods(), 9);
    QCOMPARE(mission->item(0)->sequence(), 0);
    QCOMPARE(mission->item(9)->periods(), 8);
    QCOMPARE(mission->item(9)->sequence(), 9);

    mission->insertItem(9, mission->takeItem(1));

    QCOMPARE(mission->item(1)->periods(), 1);
    QCOMPARE(mission->item(1)->sequence(), 1);
    QCOMPARE(mission->item(9)->periods(), 0);
    QCOMPARE(mission->item(9)->sequence(), 9);

    QCOMPARE(mission->item(3)->sequence(), 3);
    QCOMPARE(mission->item(3)->periods(), 3);
    QCOMPARE(mission->item(4)->periods(), 4);
    QCOMPARE(mission->item(4)->sequence(), 4);

    mission->moveUp(3);

    QCOMPARE(mission->item(4)->sequence(), 4);
    QCOMPARE(mission->item(4)->periods(), 3);
    QCOMPARE(mission->item(3)->sequence(), 3);
    QCOMPARE(mission->item(3)->periods(), 4);

    QCOMPARE(mission->item(7)->sequence(), 7);
    QCOMPARE(mission->item(7)->periods(), 7);
    QCOMPARE(mission->item(6)->sequence(), 6);
    QCOMPARE(mission->item(6)->periods(), 6);

    mission->moveDown(7);

    QCOMPARE(mission->item(7)->sequence(), 7);
    QCOMPARE(mission->item(7)->periods(), 6);
    QCOMPARE(mission->item(6)->sequence(), 6);
    QCOMPARE(mission->item(6)->periods(), 7);

    iMap.removeMission(mission);
}

void DataBaseTest::testVehicleCrud()
{
    IdentityMap iMap;

    VehiclePtr vehicle = iMap.createVehicle();

    QVERIFY(vehicle);

    vehicle->setName("Ridiculous vehicle");
    vehicle->setMavId(13);

    QCOMPARE(vehicle->name(), iMap.vehicle(vehicle->id())->name());
    QCOMPARE(vehicle->mavId(), iMap.vehicle(vehicle->id())->mavId());
    QCOMPARE(vehicle, iMap.vehicle(vehicle->id()));

    iMap.saveVehicle(vehicle);
    iMap.unloadVehicle(vehicle);

    QCOMPARE(vehicle->name(), iMap.vehicle(vehicle->id())->name());
    QVERIFY(vehicle != iMap.vehicle(vehicle->id()));

    iMap.removeVehicle(vehicle);

    QVERIFY(iMap.vehicle(vehicle->id()).isNull());
}
*/
