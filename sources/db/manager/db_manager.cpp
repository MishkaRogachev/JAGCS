#include "db_manager.h"

// Qt
#include <QFileInfo>
#include <QSqlError>
#include <QDebug>

// Internal
#include "db_migrator.h"

using namespace db;

DbManager::DbManager(QObject* parent):
    QObject(parent),
    m_db(QSqlDatabase::addDatabase("QSQLITE"))
{
    DbMigrationFactory factory;
    m_migrator = new DbMigrator(&factory, this);

    connect(m_migrator, &DbMigrator::versionChanged, this, &DbManager::onVersionChanged);
    connect(m_migrator, &DbMigrator::error, this, &DbManager::onDbError);
}

DbManager::~DbManager()
{
    m_db.close();
}

bool DbManager::open(const QString& dbName)
{
    QFileInfo file(dbName);
    bool exist = file.exists();

    m_db.setDatabaseName(dbName);
    bool opened = m_db.open();
    if (!opened)
    {
        this->onDbError(m_db.lastError().text());
        return false;
    }

    if (!exist) return m_migrator->migrate();

    return true;
}

bool DbManager::migrate()
{
    return m_migrator->migrate();
}

bool DbManager::drop()
{
    return m_migrator->drop();
}

void DbManager::onVersionChanged(const QDateTime& version)
{
    qDebug() << "DB version" << version;
}

void DbManager::onDbError(const QString& error)
{
    qWarning() << error;
}
