#include "sqlite_provider.h"

// Qt
#include <QFileInfo>

namespace
{
    const QString connectionType = "QSQLITE";
}

using namespace data_source;

SqliteProvider::SqliteProvider():
    m_database(QSqlDatabase::contains() ?
                   QSqlDatabase::database() : QSqlDatabase::addDatabase(::connectionType))
{}

SqliteProvider::~SqliteProvider()
{}

QSqlDatabase& SqliteProvider::database()
{
    return m_database;
}

bool SqliteProvider::open(bool& exists)
{
    QFileInfo info(m_database.databaseName());
    exists = info.exists();

    return m_database.open();
}

void SqliteProvider::setName(const QString& dbName)
{
    m_database.setDatabaseName(dbName);
}

QString SqliteProvider::dbName() const
{
    return m_database.databaseName();
}
