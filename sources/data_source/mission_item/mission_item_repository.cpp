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

    void fillItem(MissionItem* item)
    {
        item->setMissionId(query.value("mission_id").toInt());
        item->setSequence(query.value("sequence").toInt());
        item->setCommand(Command(query.value("command").toInt()));
        item->setAltitude(query.value("altitude").toFloat());
        item->setAltitudeRelative(query.value("altitude_relative").toBool());
        item->setLatitude(query.value("latitude").toDouble());
        item->setLongitude(query.value("longitude").toDouble());
        item->setRadius(query.value("radius").toFloat());
        item->setPitch(query.value("pitch").toFloat());
        item->setPeriods(query.value("periods").toInt());
    }

    void bindItem(MissionItem* item)
    {
        query.bindValue(":mission_id", item->missionId());
        query.bindValue(":sequence", item->sequence());
        query.bindValue(":command", int(item->command()));
        query.bindValue(":altitude", item->altitude());
        query.bindValue(":altitude_relative", item->isAltitudeRelative());
        query.bindValue(":latitude", item->latitude());
        query.bindValue(":longitude", item->longitude());
        query.bindValue(":radius", item->radius());
        query.bindValue(":pitch", item->pitch());
        query.bindValue(":periods", item->periods());
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
                     "mission_id INTEGER,"
                     "sequence INTEGER,"
                     "command INTEGER,"
                     "altitude REAL,"
                     "altitude_relative BOOLEAN,"
                     "latitude DOUBLE,"
                     "longitude DOUBLE,"
                     "radius REAL,"
                     "pitch REAL,"
                     "periods INTEGER)");

    return d->runQuerry();
}

bool MissionItemRepository::dropRepository()
{
    d->query.prepare("DROP TABLE mission_items");
    return d->runQuerry();
}

MissionItem* MissionItemRepository::createMissionItem()
{
    d->query.prepare("INSERT INTO mission_items (mission_id, "
                     "sequence, command, altitude, altitude_relative, "
                     "latitude, longitude, radius, pitch, periods) "
                     "VALUES (NULL, NULL, NULL, NULL, NULL, "
                     "NULL, NULL, NULL, NULL, NULL)");

    if (d->runQuerry()) return new MissionItem(d->query.lastInsertId().toInt());
    return nullptr;
}

MissionItem* MissionItemRepository::readMissionItem(int id)
{
    d->query.prepare("SELECT * FROM mission_items WHERE id = :id");
    d->query.bindValue(":id", id);

    if (d->runQuerry() && d->query.next())
    {
        auto item = new MissionItem(id);
        d->fillItem(item);
        return item;
    }
    return nullptr;
}

bool MissionItemRepository::updateMissionItem(MissionItem* item)
{
    d->query.prepare("UPDATE mission_items SET "
                     "mission_id = :mission_id,"
                     "sequence = :sequence,"
                     "command = :command,"
                     "altitude = :altitude,"
                     "altitude_relative = :altitude_relative,"
                     "latitude = :latitude,"
                     "longitude = :longitude,"
                     "radius = :radius,"
                     "pitch = :pitch,"
                     "periods = :periods "
                     "WHERE id = :id");

    d->query.bindValue(":id", item->id());
    d->bindItem(item);
    return d->runQuerry();
}

bool MissionItemRepository::deleteMissionItem(MissionItem* item)
{
    d->query.prepare("DELETE FROM mission_items WHERE id = :id");
    d->query.bindValue(":id", item->id());
    return d->runQuerry();
}

QList<MissionItem*> MissionItemRepository::queryMissionItems(int missionId)
{
    QList<MissionItem*> items;

    d->query.prepare("SELECT * FROM mission_items WHERE mission_id = :mission_id");
    d->query.bindValue(":mission_id", missionId);

    if (!d->runQuerry()) return items;

    while (d->query.next())
    {
        // TODO: Refactor to determinate method
        auto item = new MissionItem(d->query.value("id").toInt());
        d->fillItem(item);
        items.append(item);
    }

    return items;
}
