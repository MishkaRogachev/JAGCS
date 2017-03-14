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
    repository.updateMissionItem(item);

    auto compareItem = repository.readMissionItem(item->id());

    QCOMPARE(item->id(), compareItem->id());
    QCOMPARE(item->command(), compareItem->command());

    delete compareItem;

    QVERIFY(repository.deleteMissionItem(item));
    QVERIFY(!repository.readMissionItem(item->id()));

    delete item;

    repository.dropRepository();
}
