#include "vehicle_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "vehicle.h"

#include "telemetry.h"

using namespace presentation;

VehiclePresenter::VehiclePresenter(domain::TelemetryNode* node,
                                   const db::VehiclePtr& vehicle, QObject* parent):
    BasePresenter(parent),
    m_node(node),
    m_vehicle(vehicle)
{
    connect(m_node, &domain::TelemetryNode::parametersChanged,
            this, &VehiclePresenter::onParametersChanged);
}

void VehiclePresenter::updateVehicle()
{
    this->setViewProperty("name", m_vehicle->name());
    this->setViewProperty("mavId", m_vehicle->mavId());
}

void VehiclePresenter::connectView(QObject* view)
{
    if (!view) return;

    this->updateVehicle();
    this->onParametersChanged(m_node->parameters());
}

void VehiclePresenter::onParametersChanged(const QVariantMap& parameters)
{
    for (const QString& key: parameters.keys())
    {
        this->setViewProperty(key.toLatin1().data(), parameters[key]);
    }
}

