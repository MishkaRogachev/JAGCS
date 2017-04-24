#ifndef DOMAIN_FACADE_H
#define DOMAIN_FACADE_H

// Qt
#include <QScopedPointer>

namespace domain
{
    class CommunicationService;
    class VehicleService;
    class MissionService;

    class ProxyManager;

    class DomainFacade
    {
    public:
        DomainFacade();
        ~DomainFacade();

        CommunicationService* commService() const;
        VehicleService* vehicleService() const;
        MissionService* missionService() const;

        ProxyManager* proxyManager() const;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DOMAIN_FACADE_H
