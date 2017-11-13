#include "description_vehicle_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle_service.h"
#include "vehicle.h"

#include "translation_helper.h"

namespace
{
    namespace
    {
        const QList<dao::Vehicle::Type> availableTypes = {
            dao::Vehicle::Auto, dao::Vehicle::FixedWing, dao::Vehicle::FlyingWing,
            dao::Vehicle::Quadcopter, dao::Vehicle::Tricopter, dao::Vehicle::Hexcopter,
            dao::Vehicle::Octocopter, dao::Vehicle::Helicopter, dao::Vehicle::Coaxial,
            dao::Vehicle::Vtol, dao::Vehicle::Airship, dao::Vehicle::Kite, dao::Vehicle::Ornithopter
        };
    }
}

using namespace presentation;

DescriptionVehiclePresenter::DescriptionVehiclePresenter(domain::VehicleService* service,
                                                         const dao::VehiclePtr& vehicle,
                                                         QObject* parent):
    BasePresenter(parent),
    m_service(service),
    m_vehicle(vehicle)
{
    connect(m_service, &domain::VehicleService::vehicleChanged, this, [this]
            (const dao::VehiclePtr& vehicle) { if (vehicle == m_vehicle) this->updateStatus(); });
}

dao::VehiclePtr DescriptionVehiclePresenter::vehicle() const
{
    return m_vehicle;
}

void DescriptionVehiclePresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_vehicle->name());
    this->setViewProperty(PROPERTY(mavId), m_vehicle->mavId());
    this->setViewProperty(PROPERTY(type), ::availableTypes.indexOf(m_vehicle->type()));

    this->setViewProperty(PROPERTY(changed), false);
}

void DescriptionVehiclePresenter::updateStatus()
{
    this->setViewProperty(PROPERTY(online), m_vehicle->isOnline());
}

void DescriptionVehiclePresenter::save()
{
    m_vehicle->setName(this->viewProperty(PROPERTY(name)).toString());
    m_vehicle->setMavId(this->viewProperty(PROPERTY(mavId)).toInt());
    m_vehicle->setType(::availableTypes.at(this->viewProperty(PROPERTY(type)).toInt()));

    if (!m_service->save(m_vehicle)) return;

    this->setViewProperty(PROPERTY(changed), false);
}

void DescriptionVehiclePresenter::remove()
{
    m_service->remove(m_vehicle);
}

void DescriptionVehiclePresenter::connectView(QObject* view)
{
    QStringList types;
    TranslationHelper helper;
    for (dao::Vehicle::Type type: ::availableTypes)
    {
        types.append(helper.translateVehicleType(type));
    }
    this->setViewProperty(PROPERTY(types), QVariant::fromValue(types));

    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    this->updateView();
    this->updateStatus();
}


