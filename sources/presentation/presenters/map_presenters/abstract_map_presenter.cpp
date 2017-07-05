#include "abstract_map_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

using namespace presentation;

AbstractMapPresenter::AbstractMapPresenter(QObject* object):
    BasePresenter(object)
{}

void AbstractMapPresenter::saveViewPort()
{
    settings::Provider::setValue(settings::map::centerLatitude, this->centerLatitude());
    settings::Provider::setValue(settings::map::centerLongitude, this->centerLongitude());
    settings::Provider::setValue(settings::map::zoomLevel, this->zoomLevel());
}

void AbstractMapPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->setMapCenter(settings::Provider::value(settings::map::centerLatitude).toDouble(),
                       settings::Provider::value(settings::map::centerLongitude).toDouble());
    this->setZoomLevel(settings::Provider::value(settings::map::zoomLevel).toFloat());
}

void AbstractMapPresenter::disconnectView(QObject* view)
{
    this->saveViewPort();

    BasePresenter::disconnectView(view);
}
