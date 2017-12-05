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

    switch (m_vehicle->type())
    {
    case dao::Vehicle::FixedWing:
    case dao::Vehicle::FlyingWing:
    case dao::Vehicle::Quadcopter:
    case dao::Vehicle::Tricopter:
    case dao::Vehicle::Hexcopter:
    case dao::Vehicle::Octocopter:
    case dao::Vehicle::Helicopter:
    case dao::Vehicle::Coaxial:
    case dao::Vehicle::Vtol:
    case dao::Vehicle::Airship:
    case dao::Vehicle::Kite:
    case dao::Vehicle::Ornithopter:
        instruments.append(DashboardPresenter::FlightDisplay);
        instruments.append(DashboardPresenter::NavigationDisplay);
        break;
    default:
        break;
    }

    return instruments;
}
