#ifndef GENERIC_VEHICLE_DASHBOARD_FACTORY_H
#define GENERIC_VEHICLE_DASHBOARD_FACTORY_H

// Internal
#include "i_dashboard_factory.h"
#include "dao_traits.h"

namespace presentation
{
    class GenericDashboardFactory: public IDashboardFactory
    {
    public:
        GenericDashboardFactory(const dao::VehiclePtr& vehicle);

        DashboardPresenter* create() override;

    protected:
        dao::VehiclePtr m_vehicle;
    };
}

#endif // GENERIC_VEHICLE_DASHBOARD_FACTORY_H
