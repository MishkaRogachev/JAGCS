#include "aerial_dashboard_factory.h"

// Internal
#include "vehicle.h"

#include "domain_entry.h"
#include "telemetry_service.h"
#include "telemetry.h"

#include "dashboard_presenter.h"

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
    domain::Telemetry* node = m_entry->telemetryService()->vehicleNode(m_vehicle->id());
    if (!node) return nullptr;

    DashboardPresenter* dashboard = GenericDashboardFactory::create();

    dashboard->addInstrument("fd", 200);
    dashboard->addInstrumentPresenter("fd", new StatusPresenter(
                                  node->childNode(domain::Telemetry::Status), dashboard));
    dashboard->addInstrumentPresenter("fd", new AhrsPresenter(
                                 node->childNode(domain::Telemetry::Ahrs), dashboard));
    dashboard->addInstrumentPresenter("fd", new SatellitePresenter(
                                 node->childNode(domain::Telemetry::Satellite), dashboard));
    dashboard->addInstrumentPresenter("fd", new BarometricPresenter(
                                 node->childNode(domain::Telemetry::Barometric), dashboard));
    dashboard->addInstrumentPresenter("fd", new PitotPresenter(
                                 node->childNode(domain::Telemetry::Pitot), dashboard));
    dashboard->addInstrumentPresenter("fd", new PowerSystemPresenter(
                                 node->childNode(domain::Telemetry::PowerSystem), dashboard));

    return dashboard;

}
