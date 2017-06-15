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
                                  node->childNode(domain::TelemetryId::Status), dashboard));
    dashboard->addInstrument("fd", new AhrsPresenter(
                                 node->childNode(domain::TelemetryId::Ahrs), dashboard));
    dashboard->addInstrument("fd", new SatellitePresenter(
                                 node->childNode(domain::TelemetryId::Satellite), dashboard));
    dashboard->addInstrument("fd", new BarometricPresenter(
                                 node->childNode(domain::TelemetryId::Barometric), dashboard));
    dashboard->addInstrument("fd", new PitotPresenter(
                                 node->childNode(domain::TelemetryId::Pitot), dashboard));
    dashboard->addInstrument("hsi", new CompassPresenter(
                                 node->childNode(domain::TelemetryId::Compass), dashboard));

    return dashboard;
}
