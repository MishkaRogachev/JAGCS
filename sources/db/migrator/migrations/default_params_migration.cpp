#include "default_params_migration.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "db_facade.h"
#include "link_description.h"
#include "vehicle.h"
#include "mission.h"
#include "mission_assignment.h"

using namespace db;

bool DefaultParamsMigration::up()
{
    DbFacade facade;

    LinkDescriptionPtr defaultUdpLink = LinkDescriptionPtr::create();
    defaultUdpLink->setType(LinkDescription::Udp);
    defaultUdpLink->setPort(settings::Provider::value(settings::communication::port).toInt());
    defaultUdpLink->setName(qApp->translate("DefaultParamsMigration", "Default UDP Link"));
    defaultUdpLink->setAutoConnect(true);
    facade.save(defaultUdpLink);

    LinkDescriptionPtr defaultSerialLink = LinkDescriptionPtr::create();
    defaultSerialLink->setType(LinkDescription::Serial);
    defaultSerialLink->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());
    defaultSerialLink->setName(qApp->translate("DefaultParamsMigration", "Default Serial Link"));
    defaultSerialLink->setAutoConnect(true);
    facade.save(defaultSerialLink);

    VehiclePtr defaultVehicle = VehiclePtr::create();
    defaultVehicle->setMavId(1);
    defaultVehicle->setName(qApp->translate("DefaultParamsMigration", "Default Vehicle"));
    facade.save(defaultVehicle);

    MissionPtr defaultMission = MissionPtr::create();
    defaultMission->setName(qApp->translate("DefaultParamsMigration", "Default Mission"));
    facade.save(defaultMission);

    facade.assign(defaultMission->id(), defaultVehicle->id());

    return true;
}

bool DefaultParamsMigration::down()
{
    // Delete default values

    return true;
}

QDateTime DefaultParamsMigration::version() const
{
    return QDateTime::fromString("14:14:14-18.05.2017", format);
}
