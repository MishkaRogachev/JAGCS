#include "repositories_test.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item_repository.h"
#include "mission_repository.h"

using namespace data_source;

void RepositoriesTest::testMissionItemCrud()
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

    delete item;
    delete compareItem;
}

void RepositoriesTest::testSelectMissionItems()
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
        delete item;
    }

    {
        auto result = repository.select("periods = 3");

        QCOMPARE(result.count(), 15);
        QCOMPARE(result.first()->periods(), 3);

        while (!result.isEmpty()) delete result.takeFirst();
    }

    {
        auto result = repository.select("sequence = 7");

        QCOMPARE(result.count(), 1);
        QCOMPARE(result.first()->sequence(), 7);

        while (!result.isEmpty()) delete result.takeFirst();
    }

    {
        auto result = repository.selectMissionItems(0);

        QCOMPARE(result.count(), 5);
        QCOMPARE(result.first()->missionId(), 0);

        while (!result.isEmpty()) delete result.takeFirst();
    }
}

void RepositoriesTest::testMissionCrud()
{
    MissionRepository repository;

    Mission* mission = repository.create();

    QVERIFY(mission);
    mission->setName("Test mission");

    repository.update(mission);

    Mission* compareMission = repository.read(mission->id());

    QVERIFY(compareMission);
    QCOMPARE(mission->name(), compareMission->name());
}

void RepositoriesTest::testSelectMissions()
{
    MissionRepository repository;

    for (int i = 0; i < 6; ++i)
    {
        Mission* mission = repository.create();

        QVERIFY(mission);
        mission->setName(QString("Mission %1").arg(i));

        repository.update(mission);
    }

    {
        auto result = repository.select("name = \"Mission 3\"");

        QCOMPARE(result.count(), 1);
        QCOMPARE(result.first()->name(), QString("Mission 3"));

        while (!result.isEmpty()) delete result.takeFirst();
    }
}

