#include "vehicle_dashboard_factory.h"

// Internal
#include "telemetry_service.h"
#include "vehicle.h"

#include "dashboard_presenter.h"

using namespace presentation;

VehicleTelemetryNodeFactory::VehicleTelemetryNodeFactory(
        domain::TelemetryService* telemetryService, const db::VehiclePtr& vehicle):
    IDashboardFactory(),
    m_telemetryService(telemetryService),
    m_vehicle(vehicle)
{}

DashboardPresenter* VehicleTelemetryNodeFactory::create()
{
    auto dashboard = new DashboardPresenter(m_telemetryService->node(m_vehicle->id()));

    return dashboard;
}
