#ifndef SERVICE_REGISTRY_H
#define SERVICE_REGISTRY_H

// Qt
#include <QScopedPointer>

namespace domain
{
    class MissionService;
    class VehicleService;
    class TelemetryService;
    class VideoService;
    class CommandService;
    class CommunicationService;

    class ServiceRegistry
    {
        ServiceRegistry();
    public:
        ~ServiceRegistry();

        static ServiceRegistry* instance();

        QScopedPointer<MissionService> missionService;
        QScopedPointer<VehicleService> vehicleService;
        QScopedPointer<TelemetryService> telemetryService;
        QScopedPointer<VideoService> videoService;
        QScopedPointer<CommandService> commandService;
        QScopedPointer<CommunicationService> communicationService;

    private:
        Q_DISABLE_COPY(ServiceRegistry)
    };
}

#endif // SERVICE_REGISTRY_H
