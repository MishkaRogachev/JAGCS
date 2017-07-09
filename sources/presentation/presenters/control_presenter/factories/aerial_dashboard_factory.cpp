#include "aerial_dashboard_factory.h"

// Internal
#include "status_presenter.h"
#include "ahrs_presenter.h"
#include "satellite_presenter.h"
#include "barometric_presenter.h"
#include "pitot_presenter.h"
#include "power_system_presenter.h"

using namespace presentation;

AerialDashboardFactory::AerialDashboardFactory(domain::DomainEntry* entry,
                                               const db::VehiclePtr& vehicle):
    GenericDashboardFactory(entry, vehicle)
{}

DashboardPresenter* AerialDashboardFactory::create()
{
    DashboardPresenter* dashboard = GenericDashboardFactory::create();

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
    dashboard->addInstrument("fd", new PowerSystemPresenter(
                                 node->childNode(domain::Telemetry::PowerSystem), dashboard));

    return dashboard;

}
