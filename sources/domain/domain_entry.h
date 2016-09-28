#ifndef DOMAIN_ENTRY_H
#define DOMAIN_ENTRY_H

#include <QtGlobal>

namespace domain
{
    class SettingsProvider;
    class AbstractCommunicator;

    class DomainEntry
    {
    public:
        DomainEntry();
        ~DomainEntry();

        SettingsProvider* settings() const;
        AbstractCommunicator* communicator() const;

    private:
        class Impl;
        Impl* const d;
        Q_DISABLE_COPY(DomainEntry)
    };
}

#endif // DOMAIN_ENTRY_H
