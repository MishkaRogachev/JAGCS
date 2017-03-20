#include "repositories_test.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item_repository.h"
#include "mission_repository.h"

using namespace data_source;

void RepositoriesTest::testMissionCrud()
{
    MissionRepository repository;

    Mission* mission = new Mission();
    repository.insert(mission);

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
        Mission* mission = new Mission();
        repository.insert(mission);

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

void RepositoriesTest::testMissionItemCrud()
{
    Mission* mission = new Mission();
    {
        MissionRepository repository;
        repository.insert(mission);
    }

    MissionItemRepository repository;

    MissionItem* item = new MissionItem();
    item->setMissionId(mission->id());
    repository.insert(item);

    QVERIFY(item);

    item->setCommand(MissionItem::Landing);
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
    delete mission;
}

void RepositoriesTest::testSelectMissionItems()
{
    Mission* mission = new Mission();
    {
        MissionRepository repository;
        repository.insert(mission);
    }

    MissionItemRepository repository;

    for (int i = 0; i < 15; ++i)
    {
        MissionItem* item = new MissionItem();
        item->setMissionId(mission->id());
        repository.insert(item);
        item->setSequence(i);
        item->setCommand(MissionItem::Command(qrand() % 8 + 1));
        item->setSequence(i);
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
        auto result = repository.selectMissionItems(mission->id());

        QCOMPARE(result.count(), 15);
        QCOMPARE(result.first()->missionId(), mission->id());

        while (!result.isEmpty()) delete result.takeFirst();
    }
    delete mission;
}


