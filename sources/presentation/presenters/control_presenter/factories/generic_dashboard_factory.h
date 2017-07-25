#ifndef GENERIC_VEHICLE_DASHBOARD_FACTORY_H
#define GENERIC_VEHICLE_DASHBOARD_FACTORY_H

// Internal
#include "i_dashboard_factory.h"
#include "dao_traits.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class GenericDashboardFactory: public IDashboardFactory
    {
    public:
        GenericDashboardFactory(domain::DomainEntry* entry, const dao::VehiclePtr& vehicle);

        DashboardPresenter* create() override;

    protected:
        domain::DomainEntry* m_entry;
        dao::VehiclePtr m_vehicle;
    };
}

#endif // GENERIC_VEHICLE_DASHBOARD_FACTORY_H
