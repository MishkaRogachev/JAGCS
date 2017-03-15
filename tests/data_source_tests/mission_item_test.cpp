#include "mission_item_test.h"

// Internal
#include "mission_item.h"
#include "mission_item_repository.h"

using namespace data_source;

void MissionItemTests::testCrud()
{
    MissionItemRepository repository;

    repository.createRepository();

    auto item = repository.createMissionItem();

    item->setCommand(Command::Landing);
    item->setMissionId(45);
    item->setLatitude(34.567);
    item->setLongitude(45.241);
    item->setPeriods(2);

    repository.updateMissionItem(item);

    auto compareItem = repository.readMissionItem(item->id());

    QCOMPARE(item->missionId(), compareItem->missionId());
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

void MissionItemTests::testQueryMissionItems()
{
    MissionItemRepository repository;

    repository.createRepository();

    QList<MissionItem*> items;

    for (int i = 0; i < 17; ++i)
    {
        items.append(repository.createMissionItem());
        items.last()->setMissionId(7);
        items.last()->setSequence(i);
        items.last()->setCommand(Command(qrand() % 10));
        repository.updateMissionItem(items.last());
    }

    QList<MissionItem*> compareItems = repository.queryMissionItems(7);

    QCOMPARE(items.count(), compareItems.count());

    while (!items.isEmpty()) delete items.takeFirst();
    while (!compareItems.isEmpty()) delete compareItems.takeFirst();

    repository.dropRepository();
}
