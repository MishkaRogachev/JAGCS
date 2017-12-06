#include "navigation_display_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

NavigationDisplayPresenter::NavigationDisplayPresenter(QObject* parent):
    AbstractInstrumentPresenter(parent)
{}

void NavigationDisplayPresenter::connectNode(domain::Telemetry* node)
{
    this->chainNode(node->childNode(domain::Telemetry::Compass),
                    std::bind(&NavigationDisplayPresenter::updateCompas, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Satellite),
                    std::bind(&NavigationDisplayPresenter::updateSatellite, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::HomePosition),
                    std::bind(&NavigationDisplayPresenter::updateHome, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Navigator),
                    std::bind(&NavigationDisplayPresenter::updateNavigator, this, std::placeholders::_1));
    this->chainNode(node->childNode(domain::Telemetry::Wind),
                    std::bind(&NavigationDisplayPresenter::updateWind, this, std::placeholders::_1));
}

void NavigationDisplayPresenter::updateCompas(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(compassEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(compassOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(heading), parameters.value(domain::Telemetry::Heading, 0));
}

void NavigationDisplayPresenter::updateSatellite(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(satelliteEnabled), parameters.value(domain::Telemetry::Enabled, false));
    this->setViewProperty(PROPERTY(satelliteOperational), parameters.value(domain::Telemetry::Operational, false));
    this->setViewProperty(PROPERTY(fix), parameters.value(domain::Telemetry::Fix, 0));
    this->setViewProperty(PROPERTY(coordinate), parameters.value(domain::Telemetry::Coordinate, 0));
    this->setViewProperty(PROPERTY(groundspeed), parameters.value(domain::Telemetry::Groundspeed, 0));
    this->setViewProperty(PROPERTY(course), parameters.value(domain::Telemetry::Course, 0));
    this->setViewProperty(PROPERTY(satelliteAltitude), parameters.value(domain::Telemetry::Altitude, 0));
    this->setViewProperty(PROPERTY(eph), parameters.value(domain::Telemetry::Eph, 0));
    this->setViewProperty(PROPERTY(epv), parameters.value(domain::Telemetry::Epv, 0));
    this->setViewProperty(PROPERTY(satellitesVisible), parameters.value(domain::Telemetry::SatellitesVisible, 0));
}

void NavigationDisplayPresenter::updateHome(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(homeAltitude), parameters.value(domain::Telemetry::Altitude, 0));
}

void NavigationDisplayPresenter::updateNavigator(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewsProperty(PROPERTY(targetBearing), parameters.value(domain::Telemetry::TargetBearing, 0));
    this->setViewsProperty(PROPERTY(desiredHeading), parameters.value(domain::Telemetry::DesiredHeading, 0));
    this->setViewsProperty(PROPERTY(targetDistance), parameters.value(domain::Telemetry::TargetDistance, 0));
    this->setViewsProperty(PROPERTY(trackError), parameters.value(domain::Telemetry::TrackError, 0));
}

void NavigationDisplayPresenter::updateWind(const domain::Telemetry::TelemetryMap& parameters)
{
    this->setViewProperty(PROPERTY(windDirection), parameters.value(domain::Telemetry::Yaw, false));
    this->setViewProperty(PROPERTY(windSpeed), parameters.value(domain::Telemetry::Speed, false));
}
