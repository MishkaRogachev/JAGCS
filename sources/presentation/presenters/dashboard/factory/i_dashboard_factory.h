#ifndef I_DASHBOARD_FACTORY_H
#define I_DASHBOARD_FACTORY_H

#include <QVariant>

namespace presentation
{
    class IDashboardFactory
    {
    public:
        IDashboardFactory() {}
        virtual ~IDashboardFactory() {}

        virtual QVariantList create() = 0;
    };
}

#endif // I_DASHBOARD_FACTORY_H
