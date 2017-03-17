#include "entities_test.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item_repository.h"
#include "mission_repository.h"

using namespace data_source;

void EntitiesTest::testMissionItemCrud()
{
    MissionItemRepository repository;

    MissionItem* item = repository.create();

    QVERIFY(item);

    item->setCommand(MissionItem::Landing);
    item->setMissionId(45);
    item->setLatitude(34.567);
    item->setLongitude(45.241);
    item->setPeriods(2);

    repository.update(item);

    MissionItem* compareItem = repository.read(item->id());

    QVERIFY(compareItem);

    QCOMPARE(item->missionId(), compareItem->missionId());
    QCOMPARE(item->command(), compareItem->command());
    QVERIFY(qFuzzyCompare(item->latitude(), compareItem->latitude()));
    QVERIFY(qFuzzyCompare(item->longitude(), compareItem->longitude()));
    QCOMPARE(item->periods(), compareItem->periods());

    QVERIFY(repository.remove(item));
    QVERIFY(!repository.read(item->id()));
}

void EntitiesTest::testSelectMissionItems()
{
    MissionItemRepository repository;

    for (int i = 0; i < 15; ++i)
    {
        MissionItem* item = repository.create();
        item->setSequence(i);
        item->setCommand(MissionItem::Command(qrand() % 8 + 1));
        item->setSequence(i);
        item->setMissionId(i % 3);
        item->setPeriods(3);
        repository.update(item);
    }

    QCOMPARE(repository.select("periods = 3").count(), 15);
    QCOMPARE(repository.select("sequence = 7").first()->sequence(), 7);
    QCOMPARE(repository.selectMissionItems(0).count(), 5);
}

void EntitiesTest::testMissionCrud()
{
//    MissionRepository repository;

//    auto mission = repository.create();

//    QVERIFY(mission.isValid());
//    mission.setName("Test mission");

//    repository.update(mission);

}

