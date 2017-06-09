#include "vehicle_dashboard_factory.h"

// Internal
#include "telemetry.h"
#include "vehicle.h"

#include "dashboard_presenter.h"
#include "attitude_presenter.h"

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

    dashboard->addInstrument("fd", new AttitudePresenter(node->childNode(telemetry::ahrs),
                                                         dashboard));

    return dashboard;
}
