#include "map_presenter.h"

// Internal
#include "settings_provider.h"
#include "settings.h"

#include "mission.h"
#include "vehicle.h"

#include "mission_line_map_item_model.h"
#include "mission_point_map_item_model.h"
#include "vehicle_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

using namespace presentation;

class MapPresenter::Impl
{
public:
    MissionLineMapItemModel lineModel;
    MissionPointMapItemModel pointModel;
    VehicleMapItemModel vehicleModel;
};

MapPresenter::MapPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

MapPresenter::~MapPresenter()
{
    if (m_view) this->saveMapViewport();

    delete d;
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
    this->setViewProperty(PROPERTY(vehicleModel), QVariant::fromValue(&d->vehicleModel));
    this->setViewProperty(PROPERTY(lineModel), QVariant::fromValue(&d->lineModel));
    this->setViewProperty(PROPERTY(pointModel), QVariant::fromValue(&d->pointModel));

    connect(view, SIGNAL(saveMapViewport()), this, SLOT(saveMapViewport()));

    this->updateMapViewport();
}

void MapPresenter::addMission(domain::Mission* mission)
{
    d->lineModel.addMission(mission);

    connect(mission, &domain::Mission::missionItemsChanged,
            this, &MapPresenter::updateMissionItems);

    this->updateMissionItems();
}

void MapPresenter::removeMission(domain::Mission* mission)
{
    d->lineModel.removeMission(mission);

    disconnect(mission, 0, this, 0);

    this->updateMissionItems();
}

void MapPresenter::updateMissionItems()
{
    QList<domain::MissionItem*> items;

    for (domain::Mission* mission: d->lineModel.missions())
    {
        items.append(mission->items());
    }

    d->pointModel.setMissionItems(items);
}

void MapPresenter::addVehicle(domain::Vehicle* vehicle)
{
    d->vehicleModel.addVehicle(vehicle);
}

void MapPresenter::removeVehicle(domain::Vehicle* vehicle)
{
    d->vehicleModel.removeVehicle(vehicle);
}
