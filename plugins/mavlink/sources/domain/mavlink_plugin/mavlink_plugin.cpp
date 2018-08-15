#include "mavlink_plugin.h"

// Internal
#include "settings_provider.h"
#include "mavlink_settings.h"

#include "mavlink_communicator_builder.h"
#include "mavlink_communicator.h"

#include "init_mavlink_migration.h"

namespace
{
    QList<data_source::DbMigrationPtr> migrations =
    {
        QSharedPointer<data_source::InitMavlinkMigration>::create()
    };
}

using namespace domain;

MavlinkPlugin::MavlinkPlugin(QObject* parent):
    QObject(parent)
{}

data_source::AbstractCommunicator* MavlinkPlugin::createCommunicator()
{
    data_source::MavLinkCommunicatorBuilder builder;

    builder.initCommunicator();

    builder.buildIdentification(
                settings::Provider::value(settings::communication::systemId).toInt(),
                settings::Provider::value(settings::communication::componentId).toInt());
    builder.buildHandlers(); // later

    return builder.getCommunicator();
}

QList<data_source::DbMigrationPtr> MavlinkPlugin::migrations() const
{
    return ::migrations;
}
