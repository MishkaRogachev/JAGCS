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

ServiceRegistry::ServiceRegistry():
    missionService(new MissionService()),
    vehicleService(new VehicleService()),
    telemetryService(new TelemetryService(vehicleService.data())),
    videoService(new VideoService()),
    commandService(new CommandService())
{
    comm::MavLinkCommunicatorFactory comFactory(this,
                settings::Provider::value(settings::communication::systemId).toInt(),
                settings::Provider::value(settings::communication::componentId).toInt());

    communicationService.reset(&comFactory);
}

ServiceRegistry::~ServiceRegistry()
{}

ServiceRegistry* ServiceRegistry::instance()
{
    static ServiceRegistry registry;
    return &registry;
}
