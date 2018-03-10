#include "alter_link_description_migration.h"

// Qt
#include <QDebug>

using namespace db;

bool AlterLinkDescriptionMigration::up()
{
    qDebug() << "1";
    if (!m_query.prepare("DROP TABLE links") || !m_query.exec()) return false;
    qDebug() << "2";

    if (!m_query.prepare("CREATE TABLE links ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "type SMALLINT,"
                         "parameters TEXT,"
                         "autoConnect BOOLEAN)") || !m_query.exec()) return false;

    return DbMigration::up();
}

bool AlterLinkDescriptionMigration::down()
{
    if (!m_query.prepare("DROP TABLE links") || !m_query.exec()) return false;

    if (!m_query.prepare("CREATE TABLE links ("
                         "id INTEGER PRIMARY KEY NOT NULL,"
                         "name STRING,"
                         "type SMALLINT,"
                         "port INTEGER,"
                         "device STRING,"
                         "baudRate INTEGER,"
                         "autoConnect BOOLEAN)") || !m_query.exec()) return false;

    return true;
}

QDateTime AlterLinkDescriptionMigration::version() const
{
    return QDateTime::fromString("2018.03.08-14:58:50", format);
}
