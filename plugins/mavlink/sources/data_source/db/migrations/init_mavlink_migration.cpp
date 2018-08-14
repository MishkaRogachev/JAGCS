#include "init_mavlink_migration.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"

using namespace data_source;

bool InitMavlinkMigration::upImpl()
{
    if (!this->exec(QString("INSERT INTO link_protocols (name, description) "
                            "VALUES (\'MAVLink\', \'%1\')").arg(
                        qApp->translate("InitMavlinkMigration",
                                        "MAVLink communication protocol")))) return false;

    if (!this->exec(QString("INSERT INTO link_descriptions (name, type, parameters, protocolId, autoConnect) "
                            "VALUES (\'%1\', %2, \'BaudRate=57600\',"
                            "(SELECT id FROM link_protocols WHERE name = \'MAVLink\'), true)").arg(
                        qApp->translate("InitMavlinkMigration",
                                        "Serial Link")).arg(dto::LinkDescription::Serial))) return false;

    if (!this->exec(QString("INSERT INTO link_descriptions (name, type, parameters, protocolId, autoConnect) "
                            "VALUES (\'%1\', %2, \'Port=14550|UdpAutoResponse=true\',"
                            "(SELECT id FROM link_protocols WHERE name = \'MAVLink\'), true)").arg(
                        qApp->translate("InitMavlinkMigration",
                                        "UDP Link")).arg(dto::LinkDescription::Udp))) return false;


    return AbstractMigration::upImpl();
}

bool InitMavlinkMigration::downImpl()
{
    if (!m_query.prepare(QString("DELETE FROM link_protocols WHERE name=\'MAVLink\'")) ||
        !m_query.exec()) return false;

    return true;
}

QString InitMavlinkMigration::version() const
{
    return "mavlink_2018.08.10-16:28_init";
}
