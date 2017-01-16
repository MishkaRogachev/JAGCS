#include "map_presenter.h"

// Internal
#include "settings_provider.h"
#include "settings.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

using namespace presentation;

MapPresenter::MapPresenter(QObject* parent):
    BasePresenter(parent)
{}

MapPresenter::~MapPresenter()
{
    if (m_view) this->saveMapViewport();
}

void MapPresenter::updateMapViewport()
{
    this->setViewProperty(PROPERTY(zoomLevel), domain::SettingsProvider::value(
                              domain::map_settings::zoomLevel));
    QGeoCoordinate center(domain::SettingsProvider::value(
                              domain::map_settings::centerLatitude).toDouble(),
                          domain::SettingsProvider::value(
                              domain::map_settings::centerLongitude).toDouble());
    this->setViewProperty(PROPERTY(center), QVariant::fromValue(center));
}

void MapPresenter::saveMapViewport()
{
    domain::SettingsProvider::setValue(domain::map_settings::zoomLevel,
                                       this->viewProperty(PROPERTY(zoomLevel)));

    QGeoCoordinate center = this->viewProperty(PROPERTY(center)).value<QGeoCoordinate>();
    domain::SettingsProvider::setValue(domain::map_settings::centerLatitude,
                                       center.latitude());
    domain::SettingsProvider::setValue(domain::map_settings::centerLongitude,
                                       center.longitude());
}

void MapPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(saveMapViewport()), this, SLOT(saveMapViewport()));

    this->updateMapViewport();
}
