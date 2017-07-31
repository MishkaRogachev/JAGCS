#include "default_params_migration.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission_service.h"
#include "mission.h"
#include "mission_assignment.h"

#include "vehicle_service.h"
#include "vehicle.h"

#include "service_registry.h"
#include "communication_service.h"
#include "link_description.h"

using namespace dao;
using namespace db;
using namespace domain;

bool DefaultParamsMigration::up()
{
    LinkDescriptionPtr defaultUdpLink = LinkDescriptionPtr::create();
    defaultUdpLink->setType(LinkDescription::Udp);
    defaultUdpLink->setPort(settings::Provider::value(settings::communication::port).toInt());
    defaultUdpLink->setName(qApp->translate("DefaultParamsMigration", "Default UDP Link"));
    defaultUdpLink->setAutoConnect(true);
    ServiceRegistry::communicationService()->save(defaultUdpLink);

    LinkDescriptionPtr defaultSerialLink = LinkDescriptionPtr::create();
    defaultSerialLink->setType(LinkDescription::Serial);
    defaultSerialLink->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());
    defaultSerialLink->setName(qApp->translate("DefaultParamsMigration", "Default Serial Link"));
    defaultSerialLink->setAutoConnect(true);
    ServiceRegistry::communicationService()->save(defaultSerialLink);

    VehiclePtr defaultVehicle = VehiclePtr::create();
    defaultVehicle->setMavId(1);
    defaultVehicle->setName(qApp->translate("DefaultParamsMigration", "Default"));
    defaultVehicle->setType(Vehicle::Auto);
    ServiceRegistry::vehicleService()->save(defaultVehicle);

    MissionPtr defaultMission = MissionPtr::create();
    defaultMission->setName(qApp->translate("DefaultParamsMigration", "Idle"));
    ServiceRegistry::missionService()->save(defaultMission);

    ServiceRegistry::missionService()->assign(defaultMission->id(), defaultVehicle->id());

    return DbMigration::up();
}

bool DefaultParamsMigration::down()
{
    // No need to drop default values

    return true;
}

QDateTime DefaultParamsMigration::version() const
{
    return QDateTime::fromString("2017.06.29-22:33:08", format);
}
