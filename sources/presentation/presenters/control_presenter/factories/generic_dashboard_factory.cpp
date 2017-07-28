#include "generic_dashboard_factory.h"

// Internal
#include "service_registry.h"
#include "telemetry_service.h"
#include "telemetry.h"

#include "vehicle.h"

#include "dashboard_presenter.h"

#include "status_presenter.h"
#include "satellite_presenter.h"
#include "compass_presenter.h"
#include "navigator_presenter.h"
#include "battery_presenter.h"
#include "home_presenter.h"
#include "wind_presenter.h"
#include "common_command_presenter.h"
#include "mission_command_presenter.h"
#include "mission_status_presenter.h"

using namespace presentation;

GenericDashboardFactory::GenericDashboardFactory(const dao::VehiclePtr& vehicle):
    IDashboardFactory(),
    m_vehicle(vehicle)
{}

DashboardPresenter* GenericDashboardFactory::create()
{
    domain::Telemetry* node = domain::ServiceRegistry::telemetryService()->vehicleNode(
                                  m_vehicle->id());
    if (!node) return nullptr;

    DashboardPresenter* dashboard = new DashboardPresenter();

    dashboard->addInstrument("satellite", 100);
    dashboard->addInstrumentPresenter("satellite", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));

    dashboard->addInstrument("navigator", 300);
    dashboard->addInstrumentPresenter("navigator", new StatusPresenter(
                                 node->childNode(domain::Telemetry::Status), dashboard));
    dashboard->addInstrumentPresenter("navigator", new CompassPresenter(
                                 node->childNode(domain::Telemetry::Compass), dashboard));
    dashboard->addInstrumentPresenter("navigator", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));
    dashboard->addInstrumentPresenter("navigator", new NavigatorPresenter(
                                 node->childNode(domain::Telemetry::Navigator), dashboard));
    dashboard->addInstrumentPresenter("navigator", new HomePresenter(
                                 node->childNode(domain::Telemetry::Position),
                                 node->childNode(domain::Telemetry::HomePosition), dashboard));
    dashboard->addInstrumentPresenter("navigator", new WindPresenter(
                                 node->childNode(domain::Telemetry::Wind), dashboard));

    dashboard->addInstrument("status", 400);
    dashboard->addInstrumentPresenter("status", new StatusPresenter(
                                 node->childNode(domain::Telemetry::Status), dashboard));
    dashboard->addInstrumentPresenter("status", new BatteryPresenter(
                                          node->childNode(domain::Telemetry::Battery), dashboard));
    dashboard->addInstrumentPresenter("status", new CommonCommandPresenter(
                                          m_vehicle->id(), dashboard));

    dashboard->addInstrument("mission", 500);
    dashboard->addInstrumentPresenter("mission", new NavigatorPresenter(
                                          node->childNode(domain::Telemetry::Navigator), dashboard));
    dashboard->addInstrumentPresenter("mission", new MissionCommandPresenter(
                                          m_vehicle->id(), dashboard));
    dashboard->addInstrumentPresenter("mission", new MissionStatusPresenter(
                                          m_vehicle->id(), dashboard));

    return dashboard;
}
