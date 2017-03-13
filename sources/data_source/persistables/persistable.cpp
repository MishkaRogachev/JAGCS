#include "persistable.h"

// Qt
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

using namespace data_source;

Persistable::Persistable()
{}

bool Persistable::createTable()
{
    QSqlQuery query;

    query.prepare(QString("CREATE TABLE %1 ("
                  "number integer PRIMARY KEY NOT NULL"
                  ");").arg(this->tableName()));

    if (query.exec()) return true;

    return false;
}

bool Persistable::dropTable()
{
    QSqlQuery query;

    query.prepare(QString("DROP TABLE %1;").arg(this->tableName()));

    if (query.exec()) return true;
    return false;
}
