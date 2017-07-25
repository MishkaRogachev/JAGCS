#include "description_vehicle_presenter.h"

// Qt
#include <QVariant>
#include <QCoreApplication>

// Internal
#include "db_facade.h"
#include "vehicle.h"

namespace
{
    const QMap<dao::Vehicle::Type, QString> types =
    {
        { dao::Vehicle::UnknownType, qApp->translate("DescriptionVehiclePresenter", "Unknown") },
        { dao::Vehicle::Auto, qApp->translate("DescriptionVehiclePresenter", "Auto") },
        { dao::Vehicle::FixedWing, qApp->translate("DescriptionVehiclePresenter", "Fixed Wing") },
        { dao::Vehicle::FlyingWing, qApp->translate("DescriptionVehiclePresenter", "Flying Wing") },
        { dao::Vehicle::Quadcopter, qApp->translate("DescriptionVehiclePresenter", "Quadcopter") },
        { dao::Vehicle::Tricopter, qApp->translate("DescriptionVehiclePresenter", "Tricopter") },
        { dao::Vehicle::Hexcopter, qApp->translate("DescriptionVehiclePresenter", "Hexcopter") },
        { dao::Vehicle::Helicopter, qApp->translate("DescriptionVehiclePresenter", "Helicopter") },
        { dao::Vehicle::Coaxial, qApp->translate("DescriptionVehiclePresenter", "Coaxial") },
        { dao::Vehicle::Vtol, qApp->translate("DescriptionVehiclePresenter", "Vtol") },
        { dao::Vehicle::Airship, qApp->translate("DescriptionVehiclePresenter", "Airship") },
        { dao::Vehicle::Kite, qApp->translate("DescriptionVehiclePresenter", "Kite") },
        { dao::Vehicle::Ornithopter, qApp->translate("DescriptionVehiclePresenter", "Ornithopter") }
    };
}

using namespace presentation;

DescriptionVehiclePresenter::DescriptionVehiclePresenter(
        db::DbFacade* facade, const dao::VehiclePtr& vehicle, QObject* parent):
    BasePresenter(parent),
    m_facade(facade),
    m_vehicle(vehicle)
{
    connect(m_facade, &db::DbFacade::vehicleChanged, this, [this]
            (const dao::VehiclePtr& vehicle) {
        if (vehicle == m_vehicle) this->updateStatus();
    });
}

dao::VehiclePtr DescriptionVehiclePresenter::vehicle() const
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


