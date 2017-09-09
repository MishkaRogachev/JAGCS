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
#include "mission_instrument_presenter.h"

using namespace presentation;

AerialDashboardFactory::AerialDashboardFactory(const dao::VehiclePtr& vehicle):
    GenericDashboardFactory(vehicle)
{}

DashboardPresenter* AerialDashboardFactory::create()
{
    domain::Telemetry* node = domain::ServiceRegistry::telemetryService()->vehicleNode(
                                  m_vehicle->id());
    if (!node) return nullptr;

    DashboardPresenter* dashboard = GenericDashboardFactory::create();

    BaseInstrumentPresenter* pitot = new PitotPresenter(
                                         node->childNode(domain::Telemetry::Pitot), dashboard);
    BaseInstrumentPresenter* barometric = new BarometricPresenter(
                                              node->childNode(domain::Telemetry::Barometric), dashboard);

    dashboard->addInstrument("fd", 200);
    dashboard->addInstrumentPresenter("fd", m_status);
    dashboard->addInstrumentPresenter("fd", new AhrsPresenter(
                                          node->childNode(domain::Telemetry::Ahrs), dashboard));
    dashboard->addInstrumentPresenter("fd", m_satellite);
     dashboard->addInstrumentPresenter("fd", m_navigator);
    dashboard->addInstrumentPresenter("fd", barometric);
    dashboard->addInstrumentPresenter("fd", pitot);
    dashboard->addInstrumentPresenter("fd", new RangefinderPresenter(
                                          node->childNode(domain::Telemetry::Rangefinder), dashboard));
    dashboard->addInstrumentPresenter("fd", new PowerSystemPresenter(
                                          node->childNode(domain::Telemetry::PowerSystem), dashboard));
    dashboard->addInstrumentPresenter("fd", new HomeAltitudePresenter(
                                          node->childNode(domain::Telemetry::HomePosition), dashboard));

    dashboard->addInstrument("aircraftControl", 500);
    dashboard->addInstrumentPresenter("aircraftControl", m_status);
    dashboard->addInstrumentPresenter("aircraftControl", m_satellite);
    dashboard->addInstrumentPresenter("aircraftControl", pitot);
    dashboard->addInstrumentPresenter("aircraftControl", m_commander);
    dashboard->addInstrumentPresenter("aircraftControl", new MissionInstrumentPresenter(
                                          m_vehicle->id(), dashboard));

    return dashboard;

}
