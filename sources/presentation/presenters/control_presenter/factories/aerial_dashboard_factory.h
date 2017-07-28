#ifndef AERIAL_DASHBOARD_FACTORY_H
#define AERIAL_DASHBOARD_FACTORY_H

#include "generic_dashboard_factory.h"

namespace presentation
{
    class AerialDashboardFactory: public GenericDashboardFactory
    {
    public:
        AerialDashboardFactory(const dao::VehiclePtr& vehicle);

        DashboardPresenter* create() override;
    };
}

#endif // AERIAL_DASHBOARD_FACTORY_H
