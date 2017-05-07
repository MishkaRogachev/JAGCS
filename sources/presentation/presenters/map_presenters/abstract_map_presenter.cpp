#include "abstract_map_presenter.h"

// Internal
#include "settings_provider.h"

using namespace presentation;

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object)
{}

AbstractMapPresenter::~AbstractMapPresenter()
{
    // TODO: save current latitude and longitude
}

void AbstractMapPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->setMapCenter(domain::SettingsProvider::value(
                           settings::map::centerLatitude).toDouble(),
                       domain::SettingsProvider::value(
                           settings::map::centerLongitude).toDouble());

    this->setZoomLevel(domain::SettingsProvider::value(
                           settings::map::zoomLevel).toFloat());
}
