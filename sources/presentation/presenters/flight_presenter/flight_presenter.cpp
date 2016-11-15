#include "flight_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "video_presenter.h"
#include "flight_map_presenter.h"

using namespace presentation;

class FlightPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    QMap<uint8_t, QString> vehiclesAlias;

    VideoPresenter* video;
    FlightMapPresenter* map;
};

FlightPresenter::FlightPresenter(domain::VehicleService* vehicleService,
                                 QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->vehicleService = vehicleService;

    d->video = new VideoPresenter(this);
    d->map = new FlightMapPresenter(vehicleService, this);

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &FlightPresenter::onVehicleAdded);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &FlightPresenter::onVehicleRemoved);

    for (uint8_t id: vehicleService->vehileIds())
        this->onVehicleAdded(id);
}

FlightPresenter::~FlightPresenter()
{
    delete d;
}

void FlightPresenter::updateVehicles()
{
    QStringList vehicleNames = d->vehiclesAlias.values();
    this->setViewProperty(PROPERTY(vehicleNames), vehicleNames);
}

void FlightPresenter::connectView(QObject* view)
{
    d->video->setView(view->findChild<QObject*>(NAME(video)));
    d->map->setView(view->findChild<QObject*>(NAME(map)));

    connect(view, SIGNAL(vehicleSelected(QString)),
            this, SLOT(onVehicleSelected(QString)));
}

void FlightPresenter::onVehicleAdded(uint8_t id)
{
    d->vehiclesAlias[id] = tr("MAV %1").arg(id);

    if (m_view) this->updateVehicles();
}

void FlightPresenter::onVehicleRemoved(uint8_t id)
{
    d->vehiclesAlias.remove(id);

    if (m_view) this->updateVehicles();
}

void FlightPresenter::onVehicleSelected(const QString& vehicleName)
{
    QObject* vehicle = d->vehicleService->vehicle(
                           d->vehiclesAlias.key(vehicleName));
    this->setViewProperty(PROPERTY(selectedVehicle),
                          QVariant::fromValue(vehicle));
}
