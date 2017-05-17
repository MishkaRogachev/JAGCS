#include "db_migrator.h"

using namespace db;

DbMigrator::DbMigrator(QObject* parent):
    QObject(parent)
{}

void DbMigrator::create()
{
    if (m_migrations.isEmpty())
    {
        emit error(tr("Init migration does not exist!"));
        return;
    }

    if (!m_migrations.first().up())
    {
        emit error(tr("Init migration error: %1").arg(m_migrations.first().errorString()));
        return;
    }

    m_current = m_migrations.firstKey();
    emit currentChanged(m_current);
}

void DbMigrator::drop()
{

}

void DbMigrator::migrate(const QDateTime& time)
{
    for (const QDateTime& key: m_migrations)
    {

    }
}
