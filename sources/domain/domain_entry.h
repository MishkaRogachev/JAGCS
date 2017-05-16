#ifndef DOMAIN_ENTRY_H
#define DOMAIN_ENTRY_H

// Qt
#include <QScopedPointer>

namespace db
{
    class DbFacade;
}

namespace domain
{
    class VehicleService;
    class CommandService;
    class CommunicationService;

    class ProxyManager;

    class DomainEntry
    {
    public:
        DomainEntry();
        ~DomainEntry();

        db::DbFacade* dbFacade() const;

        VehicleService* vehicleService() const;
        CommandService* commandService() const;

        CommunicationService* commService() const;

        ProxyManager* proxyManager() const;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DOMAIN_ENTRY_H
