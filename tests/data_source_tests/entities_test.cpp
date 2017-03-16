#include "entities_test.h"

// Internal
#include "mission_item.h"
#include "generic_repository.h"
#include "generic_repository_impl.h"

using namespace data_source;

void EntitiesTest::testMissionItemCrud()
{
    GenericRepository<MissionItem> repository;

    auto item = repository.create();

    item.setCommand(Command::Landing);
    item.setMissionId(45);
    item.setLatitude(34.567);
    item.setLongitude(45.241);
    item.setPeriods(2);

    repository.update(item);

    auto compareItem = repository.read(item.id());

    QCOMPARE(item.missionId(), compareItem.missionId());
    QCOMPARE(item.command(), compareItem.command());
    QVERIFY(qFuzzyCompare(item.latitude(), compareItem.latitude()));
    QVERIFY(qFuzzyCompare(item.longitude(), compareItem.longitude()));
    QCOMPARE(item.periods(), compareItem.periods());

    QVERIFY(repository.remove(item));
    QVERIFY(!repository.read(item.id()).isValid());
}
/*
void MissionItemTests::testQueryMissionItems()
{
    GenericRepository repository;

    repository.createRepository();

    QList<MissionItem*> items;

    for (int i = 0; i < 17; ++i)
    {
        items.append(repository.create());
        items.last()->setMissionId(7);
        items.last()->setSequence(i);
        items.last()->setCommand(Command(qrand() % 10));
        repository.update(items.last());
    }

    items.append(repository.create());
    items.last()->setMissionId(8);
    items.last()->setSequence(0);
    items.last()->setCommand(Command(qrand() % 10));
    repository.update(items.last());

    QList<MissionItem*> compareItems = repository.queryMissionItems(7);

    QCOMPARE(items.count() - 1, compareItems.count());

    while (!items.isEmpty()) delete items.takeFirst();
    while (!compareItems.isEmpty()) delete compareItems.takeFirst();

    repository.dropRepository();
}*/
