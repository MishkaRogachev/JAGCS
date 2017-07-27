#ifndef DOMAIN_ENTRY_H
#define DOMAIN_ENTRY_H

// Qt
#include <QScopedPointer>

namespace db
{
    class DbManager;
}

namespace domain
{
    class TelemetryService;
    class VehicleService;
    class MissionService;
    class CommandService;
    class CommunicationService;
    class VideoService;

    class ProxyManager;

    class DomainEntry
    {
    public:
        DomainEntry();
        ~DomainEntry();

        db::DbManager* dbManager() const;

        TelemetryService* telemetryService() const;
        VehicleService* vehicleService() const;
        MissionService* missionService() const;
        CommandService* commandService() const;
        CommunicationService* commService() const;
        VideoService* videoService() const;

        ProxyManager* proxyManager() const;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DOMAIN_ENTRY_H
