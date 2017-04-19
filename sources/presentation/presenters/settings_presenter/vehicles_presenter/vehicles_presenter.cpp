#include "vehicles_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle_service.h"
#include "vehicle_description.h"

using namespace presentation;

class VehiclesPresenter::Impl
{
public:
    domain::VehicleService* service;
};

VehiclesPresenter::VehiclesPresenter(domain::VehicleService* service,
                                     QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;

    connect(service, &domain::VehicleService::vehicleAdded,
            this, &VehiclesPresenter::updateVehicles);
    connect(service, &domain::VehicleService::vehicleRemoved,
            this, &VehiclesPresenter::updateVehicles);
}

VehiclesPresenter::~VehiclesPresenter()
{}

void VehiclesPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(addVehicle()), this, SLOT(onAddVehicle()));

    this->updateVehicles();
}

void VehiclesPresenter::updateVehicles()
{
    this->setViewProperty(PROPERTY(vehicles),
                          QVariant::fromValue(d->service->vehicles().count()));
}

void VehiclesPresenter::onAddVehicle()
{
    auto description = data_source::VehicleDescriptionPtr::create();

    description->setName(tr("New Vehicle"));

    d->service->saveVehicle(description);
}
