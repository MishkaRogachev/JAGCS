#include "sqlite_provider.h"

// Qt
#include <QDebug>
#include <QFileInfo>

namespace
{
    const QString driver = "QSQLITE";
}

using namespace data_source;

SqliteProvider::SqliteProvider():
    m_database(QSqlDatabase::addDatabase(::driver))
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
    bool isOpened = m_database.isOpen();
    if (isOpened) m_database.close();

    m_database.setDatabaseName(dbName);

    if (isOpened) m_database.open();
}

QString SqliteProvider::dbName() const
{
    return m_database.databaseName();
}
