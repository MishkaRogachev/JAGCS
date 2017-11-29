#include "vehicle_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "vehicle.h"

#include "service_registry.h"
#include "vehicle_service.h"

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

VehiclePresenter::VehiclePresenter(QObject* parent):
    BasePresenter(parent),
    m_service(domain::ServiceRegistry::vehicleService())
{
    connect(m_service, &domain::VehicleService::vehicleChanged, this,
            [this](const dao::VehiclePtr& vehicle) {
        if (vehicle == m_vehicle) this->updateView();
    });
}

bool VehiclePresenter::checkMavId(int mavId)
{
    return mavId > 0 && mavId < 255 && m_vehicle &&
            (mavId == m_vehicle->mavId() || !m_service->employedMavIds().contains(mavId));
}

void VehiclePresenter::setVehicle(int id)
{
    m_vehicle = m_service->vehicle(id);

    this->updateView();
}

void VehiclePresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_vehicle ? m_vehicle->name() : QString());
    this->setViewProperty(PROPERTY(mavId), m_vehicle ? m_vehicle->mavId() : 0);
    this->setViewProperty(PROPERTY(type), m_vehicle ? ::availableTypes.indexOf(m_vehicle->type()) :
                                                      dao::Vehicle::UnknownType);
    this->setViewProperty(PROPERTY(online), m_vehicle && m_vehicle->isOnline());

    this->setViewProperty(PROPERTY(changed), false);
}

void VehiclePresenter::save()
{
    if (m_vehicle.isNull()) return;

    m_vehicle->setName(this->viewProperty(PROPERTY(name)).toString());
    m_vehicle->setMavId(this->viewProperty(PROPERTY(mavId)).toInt());
    int type = this->viewProperty(PROPERTY(type)).toInt();
    if (type >= 0 && type < ::availableTypes.count())
    {
        m_vehicle->setType(::availableTypes.at(this->viewProperty(PROPERTY(type)).toInt()));
    }

    if (m_service->save(m_vehicle)) this->setViewProperty(PROPERTY(changed), false);
}

void VehiclePresenter::remove()
{
    if (m_vehicle.isNull()) return;

    m_service->remove(m_vehicle);
}

void VehiclePresenter::connectView(QObject* view)
{
    QStringList types;
    TranslationHelper helper;
    for (dao::Vehicle::Type type: ::availableTypes)
    {
        types.append(helper.translateVehicleType(type));
    }
    view->setProperty(PROPERTY(types), QVariant::fromValue(types));
}


