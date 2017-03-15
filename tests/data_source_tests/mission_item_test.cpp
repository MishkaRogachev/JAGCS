#include "mission_item_test.h"

// Internal
#include "db_manager.h"
#include "mission_item.h"
#include "mission_item_repository.h"

using namespace data_source;

void MissionItemTests::testCrud()
{
    DbManager manager;
    manager.open("test_db");
    MissionItemRepository repository;

    repository.createRepository();

    auto item = repository.createMissionItem();

    item->setCommand(Command::Landing);
    item->setLatitude(34.567);
    item->setLongitude(45.241);
    item->setPeriods(2);

    repository.updateMissionItem(item);

    auto compareItem = repository.readMissionItem(item->id());

    QCOMPARE(item->command(), compareItem->command());
    QVERIFY(qFuzzyCompare(item->latitude(), compareItem->latitude()));
    QVERIFY(qFuzzyCompare(item->longitude(), compareItem->longitude()));
    QCOMPARE(item->periods(), compareItem->periods());

    delete compareItem;

    QVERIFY(repository.deleteMissionItem(item));
    QVERIFY(!repository.readMissionItem(item->id()));

    delete item;

    repository.dropRepository();
}
