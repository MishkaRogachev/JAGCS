#ifndef GENERIC_VEHICLE_DASHBOARD_FACTORY_H
#define GENERIC_VEHICLE_DASHBOARD_FACTORY_H

// Internal
#include "i_dashboard_factory.h"

#include "dao_traits.h"
#include "base_instrument_presenter.h"

namespace presentation
{
    class AbstractMapPresenter;

    class GenericDashboardFactory: public IDashboardFactory
    {
    public:
        GenericDashboardFactory(AbstractMapPresenter* map, const dao::VehiclePtr& vehicle);

        DashboardPresenter* create() override;

    protected:
        AbstractMapPresenter* m_map;
        dao::VehiclePtr m_vehicle;

        BaseInstrumentPresenter* m_satellite;
        BaseInstrumentPresenter* m_status;
        BaseInstrumentPresenter* m_compass;
        BaseInstrumentPresenter* m_navigator;
    };
}

#endif // GENERIC_VEHICLE_DASHBOARD_FACTORY_H
