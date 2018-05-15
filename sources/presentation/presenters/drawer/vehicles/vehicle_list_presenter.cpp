#include "vehicle_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

using namespace presentation;

VehicleListPresenter::VehicleListPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->vehicleService())
{
    connect(m_service, &domain::VehicleService::vehicleAdded,
            this, &VehicleListPresenter::updateVehicles);
    connect(m_service, &domain::VehicleService::vehicleRemoved,
            this, &VehicleListPresenter::updateVehicles);
}

void VehicleListPresenter::updateVehicles()
{
    QVariantList vehicleIds;
    for (const dto::VehiclePtr& vehicle: m_service->vehicles())
    {
        vehicleIds.append(vehicle->id());
    }

    this->setViewProperty(PROPERTY(vehicleIds), QVariant::fromValue(vehicleIds));
}

void VehicleListPresenter::addVehicle()
{
    m_service->addNewVehicle();
}

void VehicleListPresenter::setAutoAdd(bool add)
{
    settings::Provider::setValue(settings::communication::autoAdd, QVariant(add));
}

void VehicleListPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(autoAdd), settings::Provider::value(settings::communication::autoAdd));
}
