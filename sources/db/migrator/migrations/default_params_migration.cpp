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

#include "communication_service.h"
#include "link_description.h"

using namespace dao;
using namespace db;

bool DefaultParamsMigration::up()
{
    // FIXME: services registry
    /*domain::CommunicationService commService;

    LinkDescriptionPtr defaultUdpLink = LinkDescriptionPtr::create();
    defaultUdpLink->setType(LinkDescription::Udp);
    defaultUdpLink->setPort(settings::Provider::value(settings::communication::port).toInt());
    defaultUdpLink->setName(qApp->translate("DefaultParamsMigration", "Default UDP Link"));
    defaultUdpLink->setAutoConnect(true);
    commService.save(defaultUdpLink);

    LinkDescriptionPtr defaultSerialLink = LinkDescriptionPtr::create();
    defaultSerialLink->setType(LinkDescription::Serial);
    defaultSerialLink->setBaudRate(settings::Provider::value(settings::communication::baudRate).toInt());
    defaultSerialLink->setName(qApp->translate("DefaultParamsMigration", "Default Serial Link"));
    defaultSerialLink->setAutoConnect(true);
    commService.save(defaultSerialLink);*/

    domain::VehicleService vehicleService;
    VehiclePtr defaultVehicle = VehiclePtr::create();
    defaultVehicle->setMavId(1);
    defaultVehicle->setName(qApp->translate("DefaultParamsMigration", "Default"));
    defaultVehicle->setType(Vehicle::Auto);
    vehicleService.save(defaultVehicle);

    domain::MissionService missionService;
    MissionPtr defaultMission = MissionPtr::create();
    defaultMission->setName(qApp->translate("DefaultParamsMigration", "Idle"));
    missionService.save(defaultMission);

    missionService.assign(defaultMission->id(), defaultVehicle->id());

    return DbMigration::up();
}

bool DefaultParamsMigration::down()
{
    // Delete default values

    return true;
}

QDateTime DefaultParamsMigration::version() const
{
    return QDateTime::fromString("2017.06.29-22:33:08", format);
}
