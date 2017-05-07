#include "location_map_presenter.h"

// Qt
#include <QVariant>
#include <QGeoCoordinate>

using namespace presentation;

class LocationMapPresenter::Impl
{
public:
    domain::MissionService* service;
};

LocationMapPresenter::LocationMapPresenter(domain::MissionService* service,
                                           QObject* object):
    d(new Impl())
{
    d->service = service;
}

LocationMapPresenter::~LocationMapPresenter()
{}

void LocationMapPresenter::setMapCenter(double latitude, double longitude)
{
    QGeoCoordinate center(latitude, longitude);
    this->setViewProperty(PROPERTY(center), QVariant::fromValue(center));
}

void LocationMapPresenter::setZoomLevel(float zoomLevel)
{
    this->setViewProperty(PROPERTY(zoomLevel), zoomLevel);
}

void LocationMapPresenter::connectView(QObject* view)
{
    AbstractMapPresenter::connectView(view);
}
