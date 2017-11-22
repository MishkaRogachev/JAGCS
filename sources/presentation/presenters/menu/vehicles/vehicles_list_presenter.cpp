#include "vehicles_list_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

using namespace presentation;

VehiclesListPresenter::VehiclesListPresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::vehicleService())
{
    connect(m_service, &domain::VehicleService::vehicleAdded,
            this, &VehiclesListPresenter::updateVehicles);
    connect(m_service, &domain::VehicleService::vehicleRemoved,
            this, &VehiclesListPresenter::updateVehicles);
}

void VehiclesListPresenter::updateVehicles()
{
    QVariantList vehicleIds;
    for (const dao::VehiclePtr& vehicle: m_service->vehicles())
    {
        vehicleIds.append(vehicle->id());
    }

    this->setViewProperty(PROPERTY(vehicleIds), QVariant::fromValue(vehicleIds));
}

void VehiclesListPresenter::addVehicle()
{
    auto description = dao::VehiclePtr::create();

    description->setName(tr("New Vehicle"));

    m_service->save(description);
}

void VehiclesListPresenter::setAutoAdd(bool add)
{
    settings::Provider::setValue(settings::communication::autoAdd, QVariant(add));
}

void VehiclesListPresenter::connectView(QObject* view)
{
    view->setProperty(PROPERTY(autoAdd), settings::Provider::value(settings::communication::autoAdd));
}
