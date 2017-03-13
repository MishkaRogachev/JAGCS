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

bool MissionItemRepository::addMissionItem(MissionItem* item)
{
    d->query.prepare("INSERT INTO mission_items VALUES (NULL, :command)");
    d->query.bindValue(":command", int(item->command()));
    return d->runQuerry();
}

void MissionItemRepository::removeMissionItem(MissionItem* item)
{

}

void MissionItemRepository::updateMissionItem(MissionItem* item)
{

}
