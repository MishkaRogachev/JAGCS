#include "vehicle_dashboard_factory.h"

// Internal
#include "vehicle.h"

#include "dashboard_presenter.h"

using namespace presentation;

VehicleDashboardFactory::VehicleDashboardFactory(const dao::VehiclePtr& vehicle):
    IDashboardFactory(),
    m_vehicle(vehicle)
{}

QVariantList VehicleDashboardFactory::create()
{
    QVariantList instruments;

    // TODO: handle vehicles type & indicators

    instruments.append(DashboardPresenter::SatelliteDispaly);
    instruments.append(DashboardPresenter::FlightDisplay);
    instruments.append(DashboardPresenter::NavigationDisplay);
    instruments.append(DashboardPresenter::ControlDisplay);
    instruments.append(DashboardPresenter::MissionDisplay);

    return instruments;
}
