#include "persistable.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

using namespace data_source;

class Persistable::Impl
{
public:
    QSqlQuery query;
    int id = -1;

    bool runQuerry()
    {
        if (query.exec()) return true;
        qWarning() << query.lastError() << query.executedQuery();
        return false;
    }

};

Persistable::Persistable():
    d(new Impl())
{}

Persistable::~Persistable()
{
    delete d;
}

int Persistable::id() const
{
    return d->id;
}

bool Persistable::createTable()
{
    d->query.prepare(QString("CREATE TABLE %1 ("
                            "id INTEGER PRIMARY KEY NOT NULL, %2)").
                     arg(this->tableName(), this->tableParams()));
    return d->runQuerry();
}

bool Persistable::dropTable()
{
    d->query.prepare(QString("DROP TABLE %1;").arg(this->tableName()));

    return d->runQuerry();
}

bool Persistable::insert()
{
    d->query.prepare(QString("INSERT INTO %1 VALUES (NULL, %2)").
                     arg(this->tableName(), this->params()));

    d->query.bindValue(":command", 0);

    return d->runQuerry();
}
