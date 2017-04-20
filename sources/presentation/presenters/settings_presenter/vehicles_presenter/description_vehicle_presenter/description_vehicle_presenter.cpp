#include "description_vehicle_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle_description.h"
#include "vehicle_service.h"

using namespace presentation;

DescriptionVehiclePresenter::DescriptionVehiclePresenter(
        domain::VehicleService* service,
        const data_source::VehicleDescriptionPtr& description,
        QObject* parent):
    BasePresenter(parent),
    m_service(service),
    m_description(description)
{}

data_source::VehicleDescriptionPtr DescriptionVehiclePresenter::description() const
{
    return m_description;
}

void DescriptionVehiclePresenter::updateView()
{
    this->setViewProperty(PROPERTY(name), m_description->name());
    this->setViewProperty(PROPERTY(mavId), m_description->mavId());
    // TODO: type
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
    m_description->setName(name);
    m_service->saveVehicle(m_description);
}

void DescriptionVehiclePresenter::onSetMavId(int id)
{
    if (m_description->setMavId(id))
    {
        m_service->saveVehicle(m_description);
    }
    else
    {
        this->setViewProperty(PROPERTY(mavId), m_description->mavId());
    }
}

void DescriptionVehiclePresenter::onRemove()
{
    m_service->removeVehicle(m_description);
}
