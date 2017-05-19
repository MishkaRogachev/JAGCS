#include "abstract_map_presenter.h"

// Internal
#include "settings_provider.h"

using namespace presentation;

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object)
{}

void AbstractMapPresenter::saveViewPort()
{
    domain::SettingsProvider::setValue(settings::map::centerLatitude,
                                       this->centerLatitude());
    domain::SettingsProvider::setValue(settings::map::centerLongitude,
                                       this->centerLongitude());
    domain::SettingsProvider::setValue(settings::map::zoomLevel,
                                       this->zoomLevel());
}

void AbstractMapPresenter::connectView(QObject* view)
{
    this->setMapCenter(domain::SettingsProvider::value(
                           settings::map::centerLatitude).toDouble(),
                       domain::SettingsProvider::value(
                           settings::map::centerLongitude).toDouble());

    this->setZoomLevel(domain::SettingsProvider::value(
                           settings::map::zoomLevel).toFloat());

     connect(view, SIGNAL(saveViewPort()), this, SLOT(saveViewPort()));
}
