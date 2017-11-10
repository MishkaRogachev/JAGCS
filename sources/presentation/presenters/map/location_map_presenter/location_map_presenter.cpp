#include "location_map_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "service_registry.h"
#include "mission_item.h"

#include "mission_point_map_item_model.h"
#include "mission_line_map_item_model.h"
#include "vehicle_map_item_model.h"

using namespace presentation;

class LocationMapPresenter::Impl
{
public:
    MissionPointMapItemModel pointModel;
    MissionLineMapItemModel lineModel;
    VehicleMapItemModel vehicleModel;

    Impl():
        pointModel(domain::ServiceRegistry::missionService()),
        lineModel(domain::ServiceRegistry::missionService()),
        vehicleModel(domain::ServiceRegistry::vehicleService(),
                     domain::ServiceRegistry::telemetryService())
    {}
};

LocationMapPresenter::LocationMapPresenter(QObject* object):
    AbstractMapPresenter(object),
    d(new Impl())
{
    connect(&d->pointModel, &MissionPointMapItemModel::missionItemSelected,
            this, &LocationMapPresenter::missionItemSelected);
    connect(&d->pointModel, &MissionPointMapItemModel::holded, this, &LocationMapPresenter::holded);
}

LocationMapPresenter::~LocationMapPresenter()
{
    if (m_view) this->invokeViewMethod("saveViewport");
}

double LocationMapPresenter::centerLatitude() const
{
    QGeoCoordinate center = this->viewProperty(PROPERTY(center)).value<QGeoCoordinate>();
    return center.latitude();
}

double LocationMapPresenter::centerLongitude() const
{
    QGeoCoordinate center = this->viewProperty(PROPERTY(center)).value<QGeoCoordinate>();
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

void LocationMapPresenter::selectMissionItem(const dao::MissionItemPtr& item)
{
    d->pointModel.setSelectedItem(item);
}

void LocationMapPresenter::selectVehicle(const dao::VehiclePtr& vehicle)
{
    d->vehicleModel.setSelectedVehicle(vehicle);
}

void LocationMapPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->setViewProperty(PROPERTY(pointModel), QVariant::fromValue(&d->pointModel));
    this->setViewProperty(PROPERTY(lineModel), QVariant::fromValue(&d->lineModel));
    this->setViewProperty(PROPERTY(vehicleModel), QVariant::fromValue(&d->vehicleModel));
}
