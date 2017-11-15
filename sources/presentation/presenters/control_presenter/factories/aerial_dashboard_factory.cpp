#include "aerial_dashboard_factory.h"

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry.h"

#include "dashboard_presenter.h"

#include "ahrs_presenter.h"
#include "barometric_presenter.h"
#include "pitot_presenter.h"
#include "rangefinder_presenter.h"
#include "power_system_presenter.h"
#include "home_altitude_presenter.h"

using namespace presentation;

AerialDashboardFactory::AerialDashboardFactory(MapHandle* handle,
                                               const dao::VehiclePtr& vehicle):
    GenericDashboardFactory(handle, vehicle)
{}

DashboardPresenter* AerialDashboardFactory::create()
{
    domain::Telemetry* node = domain::ServiceRegistry::telemetryService()->vehicleNode(
                                  m_vehicle->id());
    if (!node) return nullptr;

    DashboardPresenter* dashboard = GenericDashboardFactory::create();

    dashboard->addInstrument("fd", 200);
    dashboard->addInstrumentPresenter("fd", m_status);
    dashboard->addInstrumentPresenter("fd", new AhrsPresenter(
                                          node->childNode(domain::Telemetry::Ahrs), dashboard));
    dashboard->addInstrumentPresenter("fd", m_satellite);
    dashboard->addInstrumentPresenter("fd", m_navigator);
    dashboard->addInstrumentPresenter("fd", new BarometricPresenter(
                                          node->childNode(domain::Telemetry::Barometric), dashboard));
    dashboard->addInstrumentPresenter("fd", new PitotPresenter(
                                          node->childNode(domain::Telemetry::Pitot), dashboard));
    dashboard->addInstrumentPresenter("fd", new RangefinderPresenter(
                                          node->childNode(domain::Telemetry::Rangefinder), dashboard));
    dashboard->addInstrumentPresenter("fd", new PowerSystemPresenter(
                                          node->childNode(domain::Telemetry::PowerSystem), dashboard));
    dashboard->addInstrumentPresenter("fd", new HomeAltitudePresenter(
                                          node->childNode(domain::Telemetry::HomePosition), dashboard));

    return dashboard;
}
