#include "entities_test.h"

// Qt
#include <QDebug>

// Internal
#include "db_facade.h"

#include "mission_service.h"
#include "mission.h"
#include "mission_item.h"
#include "mission_assignment.h"
#include "vehicle.h"
#include "link_description.h"
#include "video_source.h"

using namespace dao;

void EntitiesTest::testMission()
{
    domain::MissionService missionService;

    MissionPtr mission = MissionPtr::create();
    mission->setName("Some ridiculous name");

    QVERIFY2(missionService.save(mission), "Can't insert mission");
    int id = mission->id();
    QVERIFY2(id > 0, "Mission id after insert mus be > 0");

    mission->setName("Another ridiculous name");

    QVERIFY2(missionService.save(mission), "Can't update mission");

    QCOMPARE(mission, missionService.mission(id));

    mission->setName("Reload will erase this ridiculous name");

    QCOMPARE(mission, missionService.mission(id, true)); // But pointer will be the same

    QCOMPARE(mission->name(), QString("Another ridiculous name"));

    QVERIFY2(missionService.remove(mission), "Can't remove mission");
    QCOMPARE(mission->id(), 0); // Mission id must be zero after remove
}

void EntitiesTest::testMissionItems()
{
    domain::MissionService missionService;

    MissionPtr mission = MissionPtr::create();
    mission->setName("Items Mission");
    QVERIFY2(missionService.save(mission), "Can't insert mission");

    MissionItemPtr item = MissionItemPtr::create();
    item->setMissionId(mission->id());
    item->setCommand(MissionItem::Takeoff);
    item->setLatitude(45.6711);
    item->setLongitude(37.4869);
    item->setAltitude(350.75);

    QVERIFY2(missionService.save(item), "Can't insert mission item");

    QCOMPARE(missionService.missionItems(mission->id()).count(), 1);
    QCOMPARE(missionService.missionItems(mission->id()).first(), item);

    QVERIFY2(missionService.remove(item), "Can't remove item");
    QVERIFY2(missionService.remove(mission), "Can't remove mission");
}

void EntitiesTest::testVehicleDescription()
{
    db::DbFacade dbFacade;

    VehiclePtr vehicle = VehiclePtr::create();

    vehicle->setName("Ridiculous vehicle");
    vehicle->setMavId(13);
    vehicle->setType(Vehicle::FixedWing);

    QVERIFY2(dbFacade.save(vehicle), "Can't insert vehicle");
    int id = vehicle->id();
    QVERIFY2(id > 0, "Vehicle id after insert mus be > 0");

    QVERIFY2(dbFacade.vehicle(id, true), "Can't reload vehicle");

    QVERIFY2(vehicle->name() == "Ridiculous vehicle", "Vehicles names are different");
    QCOMPARE(vehicle->mavId(), 13);
    QCOMPARE(vehicle->type(), Vehicle::FixedWing);

    QVERIFY2(dbFacade.remove(vehicle), "Can't remove vehicle");
}

void EntitiesTest::testMissionAssignment()
{
    db::DbFacade dbFacade;
    domain::MissionService missionService;

    MissionPtr mission = MissionPtr::create();
    mission->setName("Assigned mission");
    QVERIFY2(missionService.save(mission), "Can't insert mission");

    VehiclePtr vehicle = VehiclePtr::create();
    vehicle->setName("Assigned vehicle");
    QVERIFY2(dbFacade.save(vehicle), "Can't insert vehicle");

    MissionAssignmentPtr assignment = MissionAssignmentPtr::create();
    assignment->setMissionId(mission->id());
    assignment->setVehicleId(vehicle->id());
    QVERIFY2(missionService.save(assignment), "Can't insert assignment");

    QCOMPARE(missionService.missionAssignment(mission->id()), assignment);
    QCOMPARE(missionService.vehicleAssignment(vehicle->id()), assignment);

    QVERIFY2(missionService.remove(assignment), "Can't remove assignment");

    QVERIFY2(missionService.missionAssignment(mission->id()).isNull(), "Unassigned must be null");

    QVERIFY2(missionService.remove(mission), "Can't remove mission");
    QVERIFY2(dbFacade.remove(vehicle), "Can't remove vehicle");
}

void EntitiesTest::testLinkDescription()
{
    db::DbFacade dbFacade;

    LinkDescriptionPtr link = LinkDescriptionPtr::create();
    link->setName("UDP link");
    link->setType(LinkDescription::Udp);
    link->setPort(8080);

    QVERIFY2(dbFacade.save(link), "Can't insert link");
    dbFacade.link(link->id(), true);

    QVERIFY2(link->name() == "UDP link", "Link name are different");
    QCOMPARE(link->type(), LinkDescription::Udp);
    QCOMPARE(link->port(), 8080);

    QVERIFY2(dbFacade.remove(link), "Can't remove link");
}

void EntitiesTest::testVideoSource()
{
    db::DbFacade dbFacade;

    VideoSourcePtr video = VideoSourcePtr::create();
    video->setType(VideoSource::Device);
    video->setSource("/dev/video1");

    QVERIFY2(dbFacade.save(video), "Can't insert video source");

    QCOMPARE(video->type(), VideoSource::Device);
    QVERIFY2(video->source() == "/dev/video1", "Video sources are different");

    QVERIFY2(dbFacade.remove(video), "Can't remove video source");
}
