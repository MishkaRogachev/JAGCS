#include "init_mavlink_migration.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "settings_provider.h"

using namespace data_source;

bool InitMavlinkMigration::up()
{
    if (!m_query.prepare(QString("INSERT INTO link_protocols (name, description) "
                                 "VALUES (\'MAVLink\', \'%1\')").arg(
                             qApp->translate("InitMavlinkMigration",
                                             "MAVLink communication protocol")))||
        !m_query.exec()) return false;

    return DbMigration::up();
}

bool InitMavlinkMigration::down()
{
    if (!m_query.prepare(QString("DELETE FROM link_protocols WHERE name=\'MAVLink\'")) ||
        !m_query.exec()) return false;

    return true;
}

QString InitMavlinkMigration::version() const
{
    return "mavlink_2018.08.10-16:28";
}
