#include "flight_presenter.h"

// Qt
#include <QMap>
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle_description.h"

#include "settings_provider.h"

#include "vehicle_service.h"
#include "base_vehicle.h"

#include "video_presenter.h"

using namespace presentation;

class FlightPresenter::Impl
{
public:
    domain::VehicleService* vehicleService;

    VideoPresenter* video;
};

FlightPresenter::FlightPresenter(domain::VehicleService* vehicleService,
                                 QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->vehicleService = vehicleService;

    d->video = new VideoPresenter(this);

    connect(vehicleService, &domain::VehicleService::vehicleAdded,
            this, &FlightPresenter::updateVehicles);
    connect(vehicleService, &domain::VehicleService::vehicleRemoved,
            this, &FlightPresenter::updateVehicles);
}

FlightPresenter::~FlightPresenter()
{}

void FlightPresenter::updateVehicles()
{
    QStringList vehicleNames;
    for (const data_source::VehicleDescriptionPtr& description:
         d->vehicleService->descriptions())
    {
        vehicleNames.append(description->name());
    }
    this->setViewProperty(PROPERTY(vehicleNames), vehicleNames);
}

void FlightPresenter::connectView(QObject* view)
{
    d->video->setView(view->findChild<QObject*>(NAME(video)));

    connect(view, SIGNAL(vehicleSelected(QString)),
            this, SLOT(onVehicleSelected(QString)));

    this->updateVehicles();
}

void FlightPresenter::onVehicleSelected(const QString& vehicleName)
{
    for (const data_source::VehicleDescriptionPtr& description:
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
