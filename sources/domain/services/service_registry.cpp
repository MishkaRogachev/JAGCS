#include "service_registry.h"

// Internal
#include "settings_provider.h"

#include "mission_service.h"
#include "vehicle_service.h"
#include "telemetry_service.h"
#include "video_service.h"
#include "command_service.h"
#include "communication_service.h"
#include "mavlink_communicator_factory.h"

using namespace domain;

class ServiceRegistry::Impl
{
public:
    MissionService missionService;
    VehicleService vehicleService;
    TelemetryService telemetryService;
    VideoService videoService;
    CommandService commandService;
    CommunicationService* communicationService;

    Impl():
        telemetryService(&vehicleService)
    {
        comm::MavLinkCommunicatorFactory comFactory(
                    settings::Provider::value(settings::communication::systemId).toInt(),
                    settings::Provider::value(settings::communication::componentId).toInt());

        communicationService = new CommunicationService(&comFactory);
    }
};

ServiceRegistry::ServiceRegistry():
    d(new Impl())
{}

ServiceRegistry::~ServiceRegistry()
{
    delete d->communicationService;
}

ServiceRegistry* ServiceRegistry::instance()
{
    static ServiceRegistry registry;
    return &registry;
}

MissionService* ServiceRegistry::missionService()
{
    return &instance()->d->missionService;
}

VehicleService* ServiceRegistry::vehicleService()
{
    return &instance()->d->vehicleService;
}

TelemetryService* ServiceRegistry::telemetryService()
{
    return &instance()->d->telemetryService;
}

VideoService* ServiceRegistry::videoService()
{
    return &instance()->d->videoService;
}

CommandService* ServiceRegistry::commandService()
{
    return &instance()->d->commandService;
}

CommunicationService* ServiceRegistry::communicationService()
{
    return instance()->d->communicationService;
}
