#ifndef DOMAIN_ENTRY_H
#define DOMAIN_ENTRY_H

// Qt
#include <QScopedPointer>

namespace domain
{
    class VehicleService;
    class MissionService;
    class CommandService;
    class CommunicationService;

    class ProxyManager;

    class DomainEntry
    {
    public:
        DomainEntry();
        ~DomainEntry();

        VehicleService* vehicleService() const;
        MissionService* missionService() const;
        CommandService* commandService() const;

        CommunicationService* commService() const;

        ProxyManager* proxyManager() const;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DOMAIN_ENTRY_H
