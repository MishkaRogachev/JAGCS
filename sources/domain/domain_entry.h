#ifndef DOMAIN_ENTRY_H
#define DOMAIN_ENTRY_H

#include <QtGlobal>

namespace domain
{
    class SettingsProvider;
    class ConnectionManager;

    class DomainEntry
    {
    public:
        DomainEntry();
        ~DomainEntry();

        SettingsProvider* const settings;
        ConnectionManager* const manager;

    private:
        Q_DISABLE_COPY(DomainEntry)
    };
}

#endif // DOMAIN_ENTRY_H
