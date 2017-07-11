#include "description_vehicle_presenter.h"

// Qt
#include <QVariant>
#include <QCoreApplication>

// Internal
#include "db_facade.h"
#include "vehicle.h"

namespace
{
    const QMap<db::Vehicle::Type, QString> types =
    {
        { db::Vehicle::UnknownType, qApp->translate("DescriptionVehiclePresenter", "Unknown") },
        { db::Vehicle::Auto, qApp->translate("DescriptionVehiclePresenter", "Auto") },
        { db::Vehicle::FixedWing, qApp->translate("DescriptionVehiclePresenter", "Fixed Wing") },
        { db::Vehicle::FlyingWing, qApp->translate("DescriptionVehiclePresenter", "Flying Wing") },
        { db::Vehicle::Quadcopter, qApp->translate("DescriptionVehiclePresenter", "Quadcopter") },
        { db::Vehicle::Tricopter, qApp->translate("DescriptionVehiclePresenter", "Tricopter") },
        { db::Vehicle::Hexcopter, qApp->translate("DescriptionVehiclePresenter", "Hexcopter") },
        { db::Vehicle::Helicopter, qApp->translate("DescriptionVehiclePresenter", "Helicopter") },
        { db::Vehicle::Coaxial, qApp->translate("DescriptionVehiclePresenter", "Coaxial") },
        { db::Vehicle::Vtol, qApp->translate("DescriptionVehiclePresenter", "Vtol") },
        { db::Vehicle::Airship, qApp->translate("DescriptionVehiclePresenter", "Airship") },
        { db::Vehicle::Kite, qApp->translate("DescriptionVehiclePresenter", "Kite") },
        { db::Vehicle::Ornithopter, qApp->translate("DescriptionVehiclePresenter", "Ornithopter") }
    };
}

using namespace presentation;

DescriptionVehiclePresenter::DescriptionVehiclePresenter(
        db::DbFacade* facade, const db::VehiclePtr& vehicle, QObject* parent):
    BasePresenter(parent),
    m_facade(facade),
    m_vehicle(vehicle)
{
    connect(m_facade, &db::DbFacade::vehicleChanged, this, [this]
            (const db::VehiclePtr& vehicle) {
        if (vehicle == m_vehicle) this->updateStatus();
    });
}

db::VehiclePtr DescriptionVehiclePresenter::vehicle() const
{
    return m_vehicle;
}

void DescriptionVehiclePresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_vehicle->name());
    this->setViewProperty(PROPERTY(mavId), m_vehicle->mavId());
    this->setViewProperty(PROPERTY(type), ::types.keys().indexOf(m_vehicle->type()));

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
    m_vehicle->setType(::types.keys().at(this->viewProperty(PROPERTY(type)).toInt()));

    if (!m_facade->save(m_vehicle)) return;

    this->setViewProperty(PROPERTY(changed), false);
}

void DescriptionVehiclePresenter::remove()
{
    m_facade->remove(m_vehicle);
}

void DescriptionVehiclePresenter::connectView(QObject* view)
{
    QStringList types = ::types.values();
    this->setViewProperty(PROPERTY(types), QVariant::fromValue(types));

    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    this->updateView();
    this->updateStatus();
}


