#include "init_mavlink_migration.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_description.h"
#include "mavlink_traits.h"

using namespace data_source;

bool InitMavlinkMigration::upImpl()
{
    if (!this->exec(QString("INSERT INTO link_descriptions "
                            "(name, type, protocol, parameters, autoConnect) "
                            "VALUES (\'%1\', %2, \'%3\', \'BaudRate=57600\', 1)").
                    arg(qApp->translate("InitMavlinkMigration", "Serial MAVLink")).
                    arg(dto::LinkDescription::Serial).
                    arg(protocols::mavlink.first()))) return false;

    if (!this->exec(QString("INSERT INTO link_descriptions "
                            "(name, type, protocol, parameters, autoConnect) "
                            "VALUES (\'%1\', %2, \'%3\', \'Port=14550|UdpAutoResponse=true\', 1)").
                    arg(qApp->translate("InitMavlinkMigration", "UDP MAVLink")).
                    arg(dto::LinkDescription::Udp).
                    arg(protocols::mavlink.first()))) return false;

    return true;
}

bool InitMavlinkMigration::downImpl()
{
    if (!this->exec("DELETE FROM link_descriptions WHERE protocolId IN"
                    "(SELECT id FROM link_protocols WHERE name=\'MAVLink\')")) return false;

    return true;
}

QString InitMavlinkMigration::version() const
{
    return "mavlink_2018.08.10-16:28_init";
}
