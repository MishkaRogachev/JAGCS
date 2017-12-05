#ifndef VEHICLE_DASHBOARD_FACTORY_H
#define VEHICLE_DASHBOARD_FACTORY_H

// Internal
#include "i_dashboard_factory.h"

#include "dao_traits.h"

namespace presentation
{
    class VehicleDashboardFactory: public IDashboardFactory
    {
    public:
        VehicleDashboardFactory(const dao::VehiclePtr& vehicle);
        QVariantList create() override;

    protected:
        dao::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_DASHBOARD_FACTORY_H
