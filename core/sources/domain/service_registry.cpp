#include "service_registry.h"

// Qt
#include <QDebug>

// Internal
#include "mission_service.h"
#include "vehicle_service.h"
#include "telemetry_service.h"
#include "video_service.h"
#include "command_service.h"
#include "serial_device_service.h"
#include "bluetooth_service.h"
#include "communication_service.h"

using namespace domain;

ServiceRegistry* ServiceRegistry::lastCreatedRegistry = nullptr;

class ServiceRegistry::Impl
{
public:
    MissionService missionService;
    VehicleService vehicleService;
    TelemetryService telemetryService;
    VideoService videoService;
    CommandService commandService;
    SerialDeviceService serialDeviceService;
    BluetoothService bluetoothService;
    CommunicationService communicationService;

    Impl():
        vehicleService(&missionService),
        telemetryService(&vehicleService),
        communicationService(&serialDeviceService)
    {}
};

ServiceRegistry::ServiceRegistry():
    d(new Impl())
{
    ServiceRegistry::lastCreatedRegistry = this;
}

ServiceRegistry::~ServiceRegistry()
{}

ServiceRegistry* ServiceRegistry::instance()
{
    return ServiceRegistry::lastCreatedRegistry;
}

MissionService* ServiceRegistry::missionService()
{
    return &d->missionService;
}

VehicleService* ServiceRegistry::vehicleService()
{
    return &d->vehicleService;
}

TelemetryService* ServiceRegistry::telemetryService()
{
    return &d->telemetryService;
}

VideoService* ServiceRegistry::videoService()
{
    return &d->videoService;
}

CommandService* ServiceRegistry::commandService()
{
    return &d->commandService;
}

CommunicationService* ServiceRegistry::communicationService()
{
    return &d->communicationService;
}

SerialDeviceService* ServiceRegistry::serialDeviceService()
{
    return &d->serialDeviceService;
}

BluetoothService*ServiceRegistry::bluetoothService()
{
    return &d->bluetoothService;
}
