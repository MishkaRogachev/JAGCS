#ifndef VEHICLE_DASHBOARD_FACTORY_H
#define VEHICLE_DASHBOARD_FACTORY_H

// Internal
#include "i_dashboard_factory.h"
#include "db_traits.h"

namespace domain
{
    class TelemetryService;
    class CommandService;
}

namespace presentation
{
    class VehicleDashboardFactory: public IDashboardFactory
    {
    public:
        VehicleDashboardFactory(domain::TelemetryService* telemetryService,
                                domain::CommandService* commandService,
                                const db::VehiclePtr& vehicle);

        DashboardPresenter* create() override;

    private:
        domain::TelemetryService* m_telemetryService;
        domain::CommandService* m_commandService;
        db::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_DASHBOARD_FACTORY_H
