#include "data_base_test.h"

// Qt
#include <QDebug>

// Internal
#include "identity_map.h"

#include "mission.h"
#include "mission_item.h"
#include "vehicle.h"

using namespace data_source;

void DataBaseTest::testMission()
{
    IdentityMap iMap;

    MissionPtr mission = MissionPtr::create();
    mission->setName("Some ridiculous name");

    QVERIFY2(iMap.save(mission), "Can't insert mission");
    int id = mission->id();
    QVERIFY2(id > 0, "Mission id after insert mus be > 0");

    mission->setName("Another ridiculous name");

    QVERIFY2(iMap.save(mission), "Can't update mission");

    QCOMPARE(mission, iMap.readMission(id));

    mission->setName("Reload will erase this ridiculous name");

    QCOMPARE(mission, iMap.readMission(id, true)); // But pointer will be the same

    QCOMPARE(mission->name(), QString("Another ridiculous name"));

    QVERIFY2(iMap.remove(mission), "Can't remove mission");
    QCOMPARE(mission->id(), 0); // Mission id must be zero after remove
}

void DataBaseTest::testMissionItems()
{
    IdentityMap iMap;

    MissionPtr mission = MissionPtr::create();
    mission->setName("Items Mission");
    iMap.save(mission);

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

    QVERIFY2(iMap.save(mission), "Can't insert mission with items");

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
    QVERIFY2(iMap.save(mission), "Can't save mission with items");

    QVERIFY2(item->id(), "Id must be setted on insert");

    QVERIFY2(iMap.remove(mission), "Can't remove mission");
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

    QVERIFY2(iMap.save(mission), "Can't save mission with 15 items");

    QVERIFY2(iMap.readMission(mission->id(), true), "Can't reload mission");
    QCOMPARE(mission->items().count(), 15);

    for (int i = 0; i < 15; ++i)
    {
        QCOMPARE(mission->item(i)->sequence(), i);
    }

    iMap.remove(mission->takeItem(3));
    QCOMPARE(mission->item(3)->sequence(), 3);
    QCOMPARE(mission->item(3)->periods(), 4);

    item = MissionItemPtr::create();
    item->setCommand(MissionItem::Waypoint);
    mission->insertItem(2, item);
    QCOMPARE(mission->item(2)->sequence(), 2);

    mission->exchangePosition(4, 7);
    QCOMPARE(mission->item(4)->sequence(), 4);
    QCOMPARE(mission->item(4)->periods(), 7);
    QCOMPARE(mission->item(7)->sequence(), 7);
    QCOMPARE(mission->item(7)->periods(), 4);

    QVERIFY2(iMap.readMission(mission->id(), true), "Can't reload mission");

    for (int i = 0; i < 15; ++i)
    {
        QCOMPARE(mission->item(i)->sequence(), i);
    }

    item = MissionItemPtr::create();
    item->setCommand(MissionItem::Landing);
    mission->setItem(19, item);

    QCOMPARE(mission->items().count(), 20);
    for (int i = 0; i < 20; ++i)
    {
        QCOMPARE(mission->item(i)->sequence(), i);
    }

    QVERIFY2(iMap.remove(mission), "Can't remove mission");
}

void DataBaseTest::testVehicle()
{
    IdentityMap iMap;

    VehiclePtr vehicle = VehiclePtr::create();

    vehicle->setName("Ridiculous vehicle");
    vehicle->setMavId(13);

    QVERIFY2(iMap.save(vehicle), "Can't insert vehicle");
    int id = vehicle->id();
    QVERIFY2(id > 0, "Vehicle id after insert mus be > 0");

    QVERIFY2(iMap.readVehicle(id, true), "Can't reload vehicle");

    QVERIFY2(vehicle->name() == ("Ridiculous vehicle"), "Vehicles names are different");
    QCOMPARE(vehicle->mavId(), 13);

    QVERIFY2(iMap.remove(vehicle), "Can't remove vehicle");
}
