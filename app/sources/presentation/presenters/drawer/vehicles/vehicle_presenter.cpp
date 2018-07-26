#include "vehicle_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "service_registry.h"
#include "vehicle_service.h"

#include "translation_helper.h"

#include "vehicle.h"

namespace
{
    namespace
    {
        const QList<dto::Vehicle::Type> availableTypes = {
            dto::Vehicle::Auto, dto::Vehicle::FixedWing, dto::Vehicle::FlyingWing,
            dto::Vehicle::Quadcopter, dto::Vehicle::Tricopter, dto::Vehicle::Hexcopter,
            dto::Vehicle::Octocopter, dto::Vehicle::Helicopter, dto::Vehicle::Coaxial,
            dto::Vehicle::Vtol, dto::Vehicle::Airship, dto::Vehicle::Kite, dto::Vehicle::Ornithopter
        };
    }
}

using namespace presentation;

VehiclePresenter::VehiclePresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->vehicleService())
{
    connect(m_service, &domain::VehicleService::vehicleChanged, this,
            [this](const dto::VehiclePtr& vehicle) {
        if (vehicle == m_vehicle) this->updateVehicle();
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

    if (this->view()) this->updateVehicle();
}

void VehiclePresenter::updateVehicle()
{
    this->setViewProperty(PROPERTY(name), m_vehicle ? m_vehicle->name() : QString());
    this->setViewProperty(PROPERTY(mavId), m_vehicle ? m_vehicle->mavId() : 0);
    this->setViewProperty(PROPERTY(type), m_vehicle ? ::availableTypes.indexOf(m_vehicle->type()) :
                                                      dto::Vehicle::UnknownType);
    this->setViewProperty(PROPERTY(online), m_vehicle && m_vehicle->isOnline());
}

void VehiclePresenter::rename(const QString& name)
{
    if (m_vehicle.isNull()) return;

    if (name.length() > 0) // TODO: name validator
    {
        m_vehicle->setName(name);
        m_service->save(m_vehicle);
    }
    else
    {
        this->setViewProperty(PROPERTY(name), m_vehicle->name());
    }
}

void VehiclePresenter::setMavId(int mavId)
{
    if (m_vehicle.isNull()) return;

    if (this->checkMavId(mavId))
    {
        m_vehicle->setMavId(mavId);
        m_service->save(m_vehicle);
    }
    else
    {
        this->setViewProperty(PROPERTY(mavId), m_vehicle->mavId());
    }
}

void VehiclePresenter::setType(int type)
{
    if (m_vehicle.isNull()) return;

    if (type >= 0 && type < ::availableTypes.count())
    {
        m_vehicle->setType(::availableTypes.at(type));
        m_service->save(m_vehicle);
    }
    else
    {
        this->setViewProperty(PROPERTY(type), ::availableTypes.indexOf(m_vehicle->type()));
    }
}

void VehiclePresenter::remove()
{
    if (m_vehicle.isNull()) return;

    m_service->remove(m_vehicle);
}

void VehiclePresenter::connectView(QObject* view)
{
    QStringList types;
    domain::TranslationHelper helper;
    for (dto::Vehicle::Type type: ::availableTypes)
    {
        types.append(helper.translateVehicleType(type));
    }
    view->setProperty(PROPERTY(types), QVariant::fromValue(types));

    this->updateVehicle();
}


