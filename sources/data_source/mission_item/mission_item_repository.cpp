#include "mission_item_repository.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// Internal
#include "mission_item.h"

using namespace data_source;

class MissionItemRepository::Impl
{
public:
    QSqlQuery query;

    bool runQuerry()
    {
        if (query.exec()) return true;
        qWarning() << query.lastError() << query.executedQuery();
        return false;
    }
};

MissionItemRepository::MissionItemRepository():
    d(new Impl())
{}

MissionItemRepository::~MissionItemRepository()
{
    delete d;
}

bool MissionItemRepository::createRepository()
{
    d->query.prepare("CREATE TABLE mission_items ("
                     "id INTEGER PRIMARY KEY NOT NULL,"
                     "command INTEGER)");
    return d->runQuerry();
}

bool MissionItemRepository::dropRepository()
{
    d->query.prepare("DROP TABLE mission_items");
    return d->runQuerry();
}

MissionItem* MissionItemRepository::createMissionItem()
{
    d->query.prepare("INSERT INTO mission_items VALUES (NULL, :command)");
    d->query.bindValue(":command", int(Command::UnknownCommand));

    if (d->runQuerry()) return new MissionItem(d->query.lastInsertId().toInt());
    return nullptr;
}

bool MissionItemRepository::removeMissionItem(MissionItem* item)
{
    d->query.prepare("DELETE FROM mission_items WHERE id = :id");
    d->query.bindValue(":id", item->id());
    return d->runQuerry();
}

bool MissionItemRepository::updateMissionItem(MissionItem* item)
{
    d->query.prepare("UPDATE mission_items SET command = :command WHERE id = :id");
    d->query.bindValue(":command", int(item->command()));
    d->query.bindValue(":id", item->id());
    return d->runQuerry();
}
