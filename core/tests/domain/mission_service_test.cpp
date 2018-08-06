#include "mission_service_test.h"

// Qt
#include <QDebug>
#include <QSignalSpy>

// Internal
#include "service_registry.h"
#include "mission_service.h"
#include "mission.h"
#include "mission_assignment.h"
#include "mission_item.h"

#include "vehicle_service.h"
#include "vehicle.h"

using namespace dto;
using namespace domain;

void MissionServiceTest::testMission()
{
    MissionService* missionService = serviceRegistry->missionService();

    MissionPtr mission = MissionPtr::create();
    mission->setName("Some ridiculous name");

    QVERIFY2(missionService->save(mission), "Can't insert mission");
    int id = mission->id();
    QVERIFY2(id > 0, "Mission id after insert mus be > 0");

    mission->setName("Another ridiculous name");

    QVERIFY2(missionService->save(mission), "Can't update mission");

    QCOMPARE(mission, missionService->mission(id));

    QVERIFY2(missionService->remove(mission), "Can't remove mission");
}

void MissionServiceTest::testMissionItems()
{
    domain::MissionService* missionService = serviceRegistry->missionService();

    MissionPtr mission = MissionPtr::create();
    mission->setName("Items Mission");
    QVERIFY2(missionService->save(mission), "Can't insert mission");

    int id = 0;
    {
        MissionItemPtr item = MissionItemPtr::create();
        item->setMissionId(mission->id());
        item->setCommand(MissionItem::Landing);
        item->setLatitude(45.6711);
        item->setLongitude(37.4869);
        item->setAltitude(350.75);
        item->setParameter(MissionItem::AbortAltitude, 25);
        item->setParameter(MissionItem::Yaw, 180.56);

        QVERIFY2(missionService->save(item), "Can't insert mission item");
        id = item->id();
        QVERIFY2(id > 0, "Saved id must be > 0");

        QCOMPARE(missionService->missionItems(mission->id()).count(), 1);
        QCOMPARE(missionService->missionItems(mission->id()).first(), item);

        missionService->unload(item);
    }
    MissionItemPtr item = missionService->missionItem(id);

    QCOMPARE(item->command(), MissionItem::Landing);
    QCOMPARE(item->parameter(MissionItem::AbortAltitude).toInt(), 25);
    QVERIFY(qFuzzyCompare(item->parameter(MissionItem::Yaw).toFloat(), float(180.56)));

    QVERIFY2(missionService->remove(item), "Can't remove item");
    QVERIFY2(missionService->remove(mission), "Can't remove mission");
}

// TODO: dao tests
void MissionServiceTest::testVehicleDescription()
{
    domain::VehicleService* vehicleService = serviceRegistry->vehicleService();

    VehiclePtr vehicle = VehiclePtr::create();

    vehicle->setName("Ridiculous vehicle");
    vehicle->setMavId(13);
    vehicle->setType(Vehicle::FixedWing);

    QVERIFY2(vehicleService->save(vehicle), "Can't insert vehicle");
    int id = vehicle->id();
    QVERIFY2(id > 0, "Vehicle id after insert mus be > 0");

    QVERIFY2(vehicle->name() == "Ridiculous vehicle", "Vehicles names are different");
    QCOMPARE(vehicle->mavId(), 13);
    QCOMPARE(vehicle->type(), Vehicle::FixedWing);

    QVERIFY2(vehicleService->remove(vehicle), "Can't remove vehicle");
}

void MissionServiceTest::testMissionAssignment()
{
    MissionService* missionService = serviceRegistry->missionService();
    VehicleService* vehicleService = serviceRegistry->vehicleService();

    MissionPtr mission = MissionPtr::create();
    mission->setName("Assigned mission");
    QVERIFY2(missionService->save(mission), "Can't insert mission");

    VehiclePtr vehicle = VehiclePtr::create();
    vehicle->setName("Assigned vehicle");
    QVERIFY2(vehicleService->save(vehicle), "Can't insert vehicle");

    MissionAssignmentPtr assignment = MissionAssignmentPtr::create();
    assignment->setMissionId(mission->id());
    assignment->setVehicleId(vehicle->id());
    QVERIFY2(missionService->save(assignment), "Can't insert assignment");

    QCOMPARE(missionService->missionAssignment(mission->id()), assignment);
    QCOMPARE(missionService->vehicleAssignment(vehicle->id()), assignment);

    QVERIFY2(missionService->remove(assignment), "Can't remove assignment");

    QVERIFY2(missionService->missionAssignment(mission->id()).isNull(), "Unassigned must be null");

    QVERIFY2(missionService->remove(mission), "Can't remove mission");
    QVERIFY2(vehicleService->remove(vehicle), "Can't remove vehicle");
}
