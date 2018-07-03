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

    LinkDescriptionPtr udpLink = LinkDescriptionPtr::create();
    udpLink->setType(LinkDescription::Udp);
    udpLink->setName(qApp->translate("DefaultParamsMigration", "UDP Link"));
    udpLink->setParameter(LinkDescription::Port,
                          settings::Provider::value(settings::communication::udpPort).toInt());
    udpLink->setAutoConnect(true);
    linkRepository.save(udpLink);

    LinkDescriptionPtr serialLink = LinkDescriptionPtr::create();
    serialLink->setType(LinkDescription::Serial);
    serialLink->setName(qApp->translate("DefaultParamsMigration", "Serial Link"));
    serialLink->setParameter(LinkDescription::BaudRate,
                             settings::Provider::value(settings::communication::baudRate).toInt());
    serialLink->setAutoConnect(true);
    linkRepository.save(serialLink);

    GenericRepository<dto::Vehicle> vehicleRepository("vehicles");

    VehiclePtr vehicle = VehiclePtr::create();
    vehicle->setMavId(1);
    vehicle->setName(qApp->translate("DefaultParamsMigration", "MAV 1"));
    vehicle->setType(Vehicle::Auto);
    vehicleRepository.save(vehicle);

    settings::Provider::setValue(settings::vehicle::vehicle + QString::number(vehicle->id()) +
                                 "/" + settings::vehicle::instruments::status +
                                 "/" + settings::visibility, true);
    settings::Provider::setValue(settings::vehicle::vehicle + QString::number(vehicle->id()) +
                                 "/" + settings::vehicle::instruments::fd +
                                 "/" + settings::visibility, true);
    settings::Provider::setValue(settings::vehicle::vehicle + QString::number(vehicle->id()) +
                                 "/" + settings::vehicle::instruments::hsi +
                                 "/" + settings::visibility, true);

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
