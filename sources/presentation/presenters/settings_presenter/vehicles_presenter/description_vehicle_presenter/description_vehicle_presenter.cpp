#include "description_vehicle_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "db_facade.h"
#include "vehicle.h"

using namespace presentation;

DescriptionVehiclePresenter::DescriptionVehiclePresenter(
        db::DbFacade* facade, const db::VehiclePtr& vehicle, QObject* parent):
    BasePresenter(parent),
    m_facade(facade),
    m_vehicle(vehicle)
{}

db::VehiclePtr DescriptionVehiclePresenter::vehicle() const
{
    return m_vehicle;
}

void DescriptionVehiclePresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_vehicle->name());
    this->setViewProperty(PROPERTY(mavId), m_vehicle->mavId());
}

void DescriptionVehiclePresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(setName(QString)), this, SLOT(onSetName(QString)));
    connect(view, SIGNAL(setMavId(int)), this, SLOT(onSetMavId(int)));
    connect(view, SIGNAL(remove()), this, SLOT(onRemove()));

    this->updateView();
}

void DescriptionVehiclePresenter::onSetName(const QString& name)
{
    m_vehicle->setName(name);
    m_facade->save(m_vehicle);
}

void DescriptionVehiclePresenter::onSetMavId(int id)
{
    if (m_vehicle->setMavId(id))
    {
        m_facade->save(m_vehicle);
    }
    else
    {
        this->setViewProperty(PROPERTY(mavId), m_vehicle->mavId());
    }
}

void DescriptionVehiclePresenter::onRemove()
{
    m_facade->remove(m_vehicle);
}
