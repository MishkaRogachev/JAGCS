#ifndef GENERIC_VEHICLE_DASHBOARD_FACTORY_H
#define GENERIC_VEHICLE_DASHBOARD_FACTORY_H

// Internal
#include "i_dashboard_factory.h"
#include "db_traits.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class GenericDashboardFactory: public IDashboardFactory
    {
    public:
        GenericDashboardFactory(domain::DomainEntry* entry, const db::VehiclePtr& vehicle);

        DashboardPresenter* create() override;

    private:
        domain::DomainEntry* m_entry;
        db::VehiclePtr m_vehicle;
    };
}

#endif // GENERIC_VEHICLE_DASHBOARD_FACTORY_H
