#include "flight_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "abstract_vehicle.h"

#include "video_presenter.h"
#include "flight_map_presenter.h"

using namespace presentation;

class FlightPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    QMap<domain::AbstractVehicle*, QString> vehicleAliases;

    VideoPresenter* video;
    FlightMapPresenter* map;
};

FlightPresenter::FlightPresenter(domain::MissionService* missionService,
                                 domain::VehicleService* vehicleService,
                                 QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->vehicleService = vehicleService;

    d->video = new VideoPresenter(this);
    d->map = new FlightMapPresenter(missionService, vehicleService, this);

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &FlightPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &FlightPresenter::onVehicleRemoved);

    for (domain::AbstractVehicle* vehicle: vehicleService->vehicles())
        this->onVehicleAdded(vehicle);
}

FlightPresenter::~FlightPresenter()
{
    delete d;
}

void FlightPresenter::updateVehicles()
{
    QStringList vehicleNames = d->vehicleAliases.values();
    this->setViewProperty(PROPERTY(vehicleNames), vehicleNames);
}

void FlightPresenter::connectView(QObject* view)
{
    d->video->setView(view->findChild<QObject*>(NAME(video)));
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    connect(view, SIGNAL(vehicleSelected(QString)),
            this, SLOT(onVehicleSelected(QString)));

    this->updateVehicles();
}

void FlightPresenter::onVehicleAdded(domain::AbstractVehicle* vehicle)
{
    d->vehicleAliases[vehicle] = tr("MAV %1").arg(vehicle->vehicleId());

    if (m_view) this->updateVehicles();
}

void FlightPresenter::onVehicleRemoved(domain::AbstractVehicle* vehicle)
{
    d->vehicleAliases.remove(vehicle);

    if (m_view) this->updateVehicles();
}

void FlightPresenter::onVehicleSelected(const QString& vehicleName)
{
    QObject* vehicle = d->vehicleAliases.key(vehicleName);
    this->setViewProperty(PROPERTY(selectedVehicle),
                          QVariant::fromValue(vehicle));
}
