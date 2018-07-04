#include "telemetry.h"

// Qt
#include <QDebug>

using namespace domain;

Telemetry::Telemetry(TelemetryId id, Telemetry* parentNode):
    QObject(parentNode),
    m_id(id),
    m_parentNode(parentNode)
{
    if (parentNode) parentNode->addChildNode(this);
}

Telemetry::~Telemetry()
{
    if (m_parentNode) m_parentNode->removeChildNode(this);
}

Telemetry::TelemetryId Telemetry::id() const
{
    return m_id;
}

QVariant Telemetry::parameter(TelemetryId id) const
{
    return m_parameters.value(id);
}

Telemetry::TelemetryMap Telemetry::parameters() const
{
    return m_parameters;
}

QList<Telemetry::TelemetryId> Telemetry::changedParameterKeys() const
{
    return m_changedParameters;
}

Telemetry::TelemetryMap Telemetry::takeChangedParameters()
{
    QMap<TelemetryId, QVariant> parameters;

    while (!m_changedParameters.isEmpty())
    {
        TelemetryId key = m_changedParameters.takeFirst();
        parameters[key] = m_parameters[key];
    }

    return parameters;
}

Telemetry* Telemetry::parentNode() const
{
    return m_parentNode;
}

Telemetry* Telemetry::childNode(TelemetryId id)
{
    if (!m_childNodes.contains(id))
    {
        new Telemetry(id, this);
    }

    return m_childNodes.value(id, nullptr);
}

Telemetry* Telemetry::childNode(const TelemetryList& path)
{
    if (path.isEmpty()) return this;

    QList<TelemetryId> rPath = path;
    Telemetry* child = this->childNode(rPath.takeFirst());

    if (!child) return nullptr;
    if (rPath.isEmpty()) return child;

    return child->childNode(rPath);
}

QList<Telemetry*> Telemetry::childNodes() const
{
    return m_childNodes.values();
}

void Telemetry::setParameter(TelemetryId key, const QVariant& value)
{
    if (m_parameters.contains(key) && m_parameters[key] == value) return;

    m_parameters[key] = value;
    m_changedParameters.append(key);
}

void Telemetry::setParameter(const TelemetryList& path, const QVariant& value)
{
    if (path.count() > 1)
    {
        Telemetry* child = this->childNode(path.at(0));
        child->setParameter(path.mid(1), value);
        return;
    }

    if (path.count() == 1) this->setParameter(path.at(0), value);
}

void Telemetry::notify()
{
    for (Telemetry* child: this->childNodes())
    {
        child->notify();
    }

    if (m_changedParameters.empty()) return;

    emit parametersChanged(this->takeChangedParameters());
    emit parametersUpdated(this->parameters());
}

void Telemetry::addChildNode(Telemetry* childNode)
{
    m_childNodes[childNode->id()] = childNode;
}

void Telemetry::removeChildNode(Telemetry* childNode)
{
    m_childNodes.remove(childNode->id());
}

