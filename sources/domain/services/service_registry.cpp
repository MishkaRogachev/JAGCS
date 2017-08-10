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
#include "communication_service.h"

using namespace domain;

class ServiceRegistry::Impl
{
public:
    MissionService* missionService;
    VehicleService* vehicleService;
    TelemetryService* telemetryService;
    VideoService* videoService;
    CommandService* commandService;
    CommunicationService* communicationService;
};

ServiceRegistry::ServiceRegistry():
    d(new Impl())
{}

ServiceRegistry::~ServiceRegistry()
{}

ServiceRegistry* ServiceRegistry::instance()
{
    static ServiceRegistry registry;
    return &registry;
}

void ServiceRegistry::init(const QString& dataBaseName)
{
    db::DbManager dbManager;
    if (!dbManager.open(dataBaseName))
    {
        qFatal("Unable to establish DB connection");
        qApp->quit();
    }

    d->missionService = new MissionService(qApp);
    d->vehicleService = new VehicleService(d->missionService, qApp);
    d->telemetryService = new TelemetryService(d->vehicleService, qApp);
    d->videoService = new VideoService(qApp);
    d->commandService = new CommandService(qApp);
    d->communicationService = new CommunicationService(qApp);

    d->communicationService->init();

    QObject::connect(qApp, &QCoreApplication::aboutToQuit, [this]() {
        delete d->communicationService;
        delete d->commandService;
        delete d->videoService;
        delete d->telemetryService;
        delete d->vehicleService;
        delete d->missionService;
    });
}

MissionService* ServiceRegistry::missionService()
{
    return instance()->d->missionService;
}

VehicleService* ServiceRegistry::vehicleService()
{
    return instance()->d->vehicleService;
}

TelemetryService* ServiceRegistry::telemetryService()
{
    return instance()->d->telemetryService;
}

VideoService* ServiceRegistry::videoService()
{
    return instance()->d->videoService;
}

CommandService* ServiceRegistry::commandService()
{
    return instance()->d->commandService;
}

CommunicationService* ServiceRegistry::communicationService()
{
    return instance()->d->communicationService;
}
