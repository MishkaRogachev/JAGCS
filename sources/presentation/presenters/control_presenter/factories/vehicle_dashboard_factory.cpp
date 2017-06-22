#include "vehicle_dashboard_factory.h"

// Internal
#include "telemetry_service.h"
#include "telemetry.h"

#include "vehicle.h"

#include "dashboard_presenter.h"
#include "status_presenter.h"
#include "ahrs_presenter.h"
#include "satellite_presenter.h"
#include "barometric_presenter.h"
#include "pitot_presenter.h"
#include "compass_presenter.h"
#include "navigator_presenter.h"
#include "battery_presenter.h"
#include "radio_presenter.h"

using namespace presentation;

VehicleDashboardFactory::VehicleDashboardFactory(domain::TelemetryService* telemetryService,
                                                 const db::VehiclePtr& vehicle):
    IDashboardFactory(),
    m_telemetryService(telemetryService),
    m_vehicle(vehicle)
{}

DashboardPresenter* VehicleDashboardFactory::create()
{
    domain::Telemetry* node = m_telemetryService->node(m_vehicle->id());
    if (!node) return nullptr;

    // TODO: vehicle type
    DashboardPresenter* dashboard = new DashboardPresenter();

    dashboard->addInstrument("satellite", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));

    dashboard->addInstrument("fd", new StatusPresenter(
                                  node->childNode(domain::Telemetry::Status), dashboard));
    dashboard->addInstrument("fd", new AhrsPresenter(
                                 node->childNode(domain::Telemetry::Ahrs), dashboard));
    dashboard->addInstrument("fd", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));
    dashboard->addInstrument("fd", new BarometricPresenter(
                                 node->childNode(domain::Telemetry::Barometric), dashboard));
    dashboard->addInstrument("fd", new PitotPresenter(
                                 node->childNode(domain::Telemetry::Pitot), dashboard));

    dashboard->addInstrument("nav", new CompassPresenter(
                                 node->childNode(domain::Telemetry::Compass), dashboard));
    dashboard->addInstrument("nav", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));
    dashboard->addInstrument("nav", new NavigatorPresenter(
                                 node->childNode(domain::Telemetry::Navigator), dashboard));

    dashboard->addInstrument("status", new BatteryPresenter(
                                 node->childNode(domain::Telemetry::Battery), dashboard));
    dashboard->addInstrument("status", new RadioPresenter(
                                 node->childNode(domain::Telemetry::Radio), dashboard));

    return dashboard;
}
