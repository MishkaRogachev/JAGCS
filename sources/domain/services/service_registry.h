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
    class SerialPortService;
    class CommunicationService;

    class ServiceRegistry
    {
    public:
        ServiceRegistry();
        virtual ~ServiceRegistry();

        static ServiceRegistry* instance();

        void init(const QString& dataBaseName);

        static MissionService* missionService();
        static VehicleService* vehicleService();
        static TelemetryService* telemetryService();
        static VideoService* videoService();
        static CommandService* commandService();
        static SerialPortService* serialPortService();
        static CommunicationService* communicationService();

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        static ServiceRegistry* lastCreatedRegistry;

        Q_DISABLE_COPY(ServiceRegistry)
    };

}

#define serviceRegistry (domain::ServiceRegistry::instance())

#endif // SERVICE_REGISTRY_H
