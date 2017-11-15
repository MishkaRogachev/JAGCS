#ifndef GENERIC_VEHICLE_DASHBOARD_FACTORY_H
#define GENERIC_VEHICLE_DASHBOARD_FACTORY_H

// Internal
#include "i_dashboard_factory.h"

#include "dao_traits.h"
#include "base_instrument_presenter.h"

namespace presentation
{
    class MapHandle;

    class GenericDashboardFactory: public IDashboardFactory
    {
    public:
        GenericDashboardFactory(MapHandle* handle, const dao::VehiclePtr& vehicle);

        DashboardPresenter* create() override;

    protected:
        MapHandle* m_handle;
        dao::VehiclePtr m_vehicle;

        BaseInstrumentPresenter* m_satellite;
        BaseInstrumentPresenter* m_status;
        BaseInstrumentPresenter* m_compass;
        BaseInstrumentPresenter* m_navigator;
    };
}

#endif // GENERIC_VEHICLE_DASHBOARD_FACTORY_H
