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
    class BluetoothService;
    class CommunicationService;

    class ServiceRegistry
    {
    public:
        ServiceRegistry();
        virtual ~ServiceRegistry();

        static ServiceRegistry* instance();

        MissionService* missionService();
        VehicleService* vehicleService();
        TelemetryService* telemetryService();
        VideoService* videoService();
        CommandService* commandService();
        SerialPortService* serialPortService();
        BluetoothService* bluetoothService();
        CommunicationService* communicationService();

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        static ServiceRegistry* lastCreatedRegistry;

        Q_DISABLE_COPY(ServiceRegistry)
    };
}

#define serviceRegistry (domain::ServiceRegistry::instance())

#endif // SERVICE_REGISTRY_H
