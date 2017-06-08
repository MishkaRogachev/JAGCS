#include "vehicle_dashboard_factory.h"

// Internal
#include "telemetry_service.h"
#include "vehicle.h"

#include "dashboard_presenter.h"
#include "artificial_horizon_presenter.h"

using namespace presentation;

VehicleDashboardFactory::VehicleDashboardFactory(domain::TelemetryService* telemetryService,
                                                 const db::VehiclePtr& vehicle):
    IDashboardFactory(),
    m_telemetryService(telemetryService),
    m_vehicle(vehicle)
{}

DashboardPresenter* VehicleDashboardFactory::create()
{
    auto dashboard = new DashboardPresenter(m_telemetryService->node(m_vehicle->id()));

    // TODO: vehicle type
    dashboard->addInstrument("af", new ArtificialHorizonPresenter(dashboard));

    return dashboard;
}
