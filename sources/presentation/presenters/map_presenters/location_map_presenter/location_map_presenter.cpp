#include "location_map_presenter.h"

// Qt
#include <QVariant>
#include <QGeoCoordinate>

// Internal
#include "mission_point_map_item_model.h"

using namespace presentation;

class LocationMapPresenter::Impl
{
public:
    MissionPointMapItemModel pointModel;

    Impl(domain::MissionService* service):
        pointModel(service)
    {}
};

LocationMapPresenter::LocationMapPresenter(domain::MissionService* service,
                                           QObject* object):
    AbstractMapPresenter(object),
    d(new Impl(service))
{}

LocationMapPresenter::~LocationMapPresenter()
{}

double LocationMapPresenter::centerLatitude() const
{
    QGeoCoordinate center = this->viewProperty(
                                PROPERTY(center)).value<QGeoCoordinate>();
    return center.latitude();
}

double LocationMapPresenter::centerLongitude() const
{
    QGeoCoordinate center = this->viewProperty(
                                PROPERTY(center)).value<QGeoCoordinate>();
    return center.longitude();
}

float LocationMapPresenter::zoomLevel() const
{
    return this->viewProperty(PROPERTY(zoomLevel)).toFloat();
}

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

    this->setViewProperty(PROPERTY(pointModel), QVariant::fromValue(&d->pointModel));
}
