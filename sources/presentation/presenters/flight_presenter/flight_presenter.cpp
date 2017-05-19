#include "flight_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "domain_entry.h"
#include "vehicle_description.h"

#include "settings_provider.h"

#include "vehicle_service.h"
#include "base_vehicle.h"

#include "video_presenter.h"
#include "location_map_presenter.h"

using namespace presentation;

class FlightPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    VideoPresenter* video;
    AbstractMapPresenter* map;
};

FlightPresenter::FlightPresenter(domain::DomainEntry* entry,
                                 QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->vehicleService = entry->vehicleService();

    d->video = new VideoPresenter(this);

    connect(d->vehicleService, &domain::VehicleService::vehicleAdded,
            this, &FlightPresenter::updateVehicles);
    connect(d->vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &FlightPresenter::updateVehicles);

    d->map = new LocationMapPresenter(entry, this);
}

FlightPresenter::~FlightPresenter()
{}

void FlightPresenter::updateVehicles()
{
    QStringList vehicleNames;
    for (const db::VehicleDescriptionPtr& description:
         d->vehicleService->descriptions())
    {
        vehicleNames.append(description->name());
    }
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

void FlightPresenter::onVehicleSelected(const QString& vehicleName)
{
    for (const db::VehicleDescriptionPtr& description:
         d->vehicleService->descriptions())
    {
        if (description->name() != vehicleName) continue;

        // TODO: specialized vehicle presenter
        QObject* vehicle = d->vehicleService->baseVehicle(description);
        this->setViewProperty(PROPERTY(selectedVehicle),
                              QVariant::fromValue(vehicle));
        return;
    }

    this->setViewProperty(PROPERTY(selectedVehicle), QVariant());
}
