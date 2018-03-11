#include "default_params_migration.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "mission.h"
#include "mission_assignment.h"
#include "vehicle.h"
#include "link_description.h"

#include "generic_repository.h"

using namespace dto;
using namespace db;

bool DefaultParamsMigration::up()
{
    GenericRepository<dto::LinkDescription> linkRepository("links");

    LinkDescriptionPtr defaultUdpLink = LinkDescriptionPtr::create();
    defaultUdpLink->setType(LinkDescription::Udp);
    defaultUdpLink->setName(qApp->translate("DefaultParamsMigration", "Default UDP Link"));
    defaultUdpLink->setParameter(LinkDescription::Port,
                                 settings::Provider::value(settings::communication::port).toInt());
    defaultUdpLink->setAutoConnect(true);
    linkRepository.save(defaultUdpLink);

    LinkDescriptionPtr defaultSerialLink = LinkDescriptionPtr::create();
    defaultSerialLink->setType(LinkDescription::Serial);
    defaultSerialLink->setName(qApp->translate("DefaultParamsMigration", "Default Serial Link"));
    defaultSerialLink->setParameter(LinkDescription::BaudRate,
                                    settings::Provider::value(settings::communication::baudRate).toInt());
    defaultSerialLink->setAutoConnect(true);
    linkRepository.save(defaultSerialLink);

    GenericRepository<dto::Vehicle> vehicleRepository("vehicles");

    VehiclePtr defaultVehicle = VehiclePtr::create();
    defaultVehicle->setMavId(1);
    defaultVehicle->setName(qApp->translate("DefaultParamsMigration", "Default"));
    defaultVehicle->setType(Vehicle::Auto);
    vehicleRepository.save(defaultVehicle);

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
