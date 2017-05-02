#ifndef DOMAIN_ENTRY_H
#define DOMAIN_ENTRY_H

// Qt
#include <QScopedPointer>

namespace domain
{
    class CommunicationService;
    class VehicleService;
    class MissionService;

    class ProxyManager;

    class DomainEntry
    {
    public:
        DomainEntry();
        ~DomainEntry();

        CommunicationService* commService() const;
        VehicleService* vehicleService() const;
        MissionService* missionService() const;

        ProxyManager* proxyManager() const;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DOMAIN_ENTRY_H
