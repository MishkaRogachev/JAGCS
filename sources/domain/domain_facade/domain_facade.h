#ifndef DOMAIN_FACADE_H
#define DOMAIN_FACADE_H

// Qt
#include <QScopedPointer>

namespace domain
{
    class DomainFacade
    {
    public:
        DomainFacade();
        ~DomainFacade();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DOMAIN_FACADE_H
