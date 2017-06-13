#include "vehicle_dashboard_factory.h"

// Internal
#include "telemetry.h"
#include "vehicle.h"

#include "dashboard_presenter.h"
#include "status_presenter.h"
#include "ahrs_presenter.h"
#include "satellite_presenter.h"
#include "barometric_presenter.h"
#include "pitot_presenter.h"
#include "compass_presenter.h"

using namespace presentation;

VehicleDashboardFactory::VehicleDashboardFactory(domain::TelemetryService* telemetryService,
                                                 const db::VehiclePtr& vehicle):
    IDashboardFactory(),
    m_telemetryService(telemetryService),
    m_vehicle(vehicle)
{}

DashboardPresenter* VehicleDashboardFactory::create()
{
    domain::TelemetryNode* node = m_telemetryService->node(m_vehicle->id());
    if (!node) return nullptr;

    // TODO: vehicle type
    DashboardPresenter* dashboard = new DashboardPresenter();

    dashboard->addInstrument("fd", new StatusPresenter(
                                  node->childNode(telemetry::status), dashboard));
    dashboard->addInstrument("fd", new AhrsPresenter(
                                 node->childNode(telemetry::ahrs), dashboard));
    dashboard->addInstrument("fd", new SatellitePresenter(
                                 node->childNode(telemetry::satellite), dashboard));
    dashboard->addInstrument("fd", new BarometricPresenter(
                                 node->childNode(telemetry::barometric), dashboard));
    dashboard->addInstrument("fd", new PitotPresenter(
                                 node->childNode(telemetry::pitot), dashboard));
    dashboard->addInstrument("hsi", new CompassPresenter(
                                 node->childNode(telemetry::compass), dashboard));

    return dashboard;
}
