#include "service_registry.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "db_manager.h"
#include "mission_service.h"
#include "vehicle_service.h"
#include "telemetry_service.h"
#include "video_service.h"
#include "command_service.h"
#include "serial_ports_service.h"
#include "communication_service.h"

using namespace domain;

ServiceRegistry* ServiceRegistry::lastCreatedRegistry = nullptr;

class ServiceRegistry::Impl
{
public:
    QScopedPointer<MissionService> missionService;
    QScopedPointer<VehicleService> vehicleService;
    QScopedPointer<TelemetryService> telemetryService;
    QScopedPointer<VideoService> videoService;
    QScopedPointer<CommandService> commandService;
    QScopedPointer<SerialPortService> serialPortService;
    QScopedPointer<CommunicationService> communicationService;
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

void ServiceRegistry::init(const QString& dataBaseName)
{
    db::DbManager dbManager;
    if (!dbManager.open(dataBaseName))
    {
        qFatal("Unable to establish DB connection");
        qApp->quit();
    }

    d->missionService.reset(new MissionService(qApp));
    d->vehicleService.reset(new VehicleService(d->missionService.data(), qApp));
    d->telemetryService.reset(new TelemetryService(d->vehicleService.data(), qApp));
    d->videoService.reset(new VideoService(qApp));
    d->commandService.reset(new CommandService(qApp));
    d->communicationService.reset(new CommunicationService(d->serialPortService.data(), qApp));

    d->communicationService->init();
}

MissionService* ServiceRegistry::missionService()
{
    return instance()->d->missionService.data();
}

VehicleService* ServiceRegistry::vehicleService()
{
    return instance()->d->vehicleService.data();
}

TelemetryService* ServiceRegistry::telemetryService()
{
    return instance()->d->telemetryService.data();
}

VideoService* ServiceRegistry::videoService()
{
    return instance()->d->videoService.data();
}

CommandService* ServiceRegistry::commandService()
{
    return instance()->d->commandService.data();
}

CommunicationService* ServiceRegistry::communicationService()
{
    return instance()->d->communicationService.data();
}

SerialPortService* ServiceRegistry::serialPortService()
{
    return instance()->d->serialPortService.data();
}
