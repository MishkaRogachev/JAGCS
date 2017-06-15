#include "telemetry_node.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

using namespace domain;

TelemetryNode::TelemetryNode(TelemetryId id, TelemetryNode* parentNode):
    QObject(parentNode),
    m_id(id),
    m_parentNode(parentNode)
{
    if (parentNode) parentNode->addChildNode(this);
}

TelemetryNode::~TelemetryNode()
{
    if (m_parentNode) m_parentNode->removeChildNode(this);
}

TelemetryId TelemetryNode::id() const
{
    return m_id;
}

QVariant TelemetryNode::parameter(TelemetryId id) const
{
    return m_parameters.value(id);
}

TelemetryMap TelemetryNode::parameters() const
{
    return m_parameters;
}

TelemetryList TelemetryNode::changedParameterKeys() const
{
    return m_changedParameters;
}

TelemetryMap TelemetryNode::takeChangedParameters()
{
    TelemetryMap parameters;

    while (!m_changedParameters.isEmpty())
    {
        TelemetryId key = m_changedParameters.takeFirst();
        parameters[key] = m_parameters[key];
    }

    return parameters;
}

TelemetryNode* TelemetryNode::parentNode() const
{
    return m_parentNode;
}

TelemetryNode* TelemetryNode::childNode(TelemetryId id)
{
    if (!m_childNodes.contains(id))
    {
        new TelemetryNode(id, this);
    }

    return m_childNodes.value(id, nullptr);
}

TelemetryNode* TelemetryNode::childNode(const TelemetryList& path)
{
    if (path.isEmpty()) return this;

    TelemetryList rPath = path;
    TelemetryNode* child = this->childNode(rPath.takeFirst());

    if (!child) return nullptr;
    if (rPath.isEmpty()) return child;

    return child->childNode(rPath);
}

QList<TelemetryNode*> TelemetryNode::childNodes() const
{
    return m_childNodes.values();
}

void TelemetryNode::setParameter(TelemetryId key, const QVariant& value)
{
    if (m_parameters.contains(key) && m_parameters[key] == value) return;

    m_parameters[key] = value;
    m_changedParameters.append(key);
}

void TelemetryNode::setParameter(const TelemetryList& path, const QVariant& value)
{
    if (path.count() > 1)
    {
        TelemetryNode* child = this->childNode(path.at(0));
        child->setParameter(path.at(1), value);
        return;
    }

    if (path.count() == 1) this->setParameter(path.at(0), value);
}

void TelemetryNode::notify()
{
    for (TelemetryNode* child: this->childNodes())
    {
        child->notify();
    }

    emit parametersChanged(this->takeChangedParameters());
}

void TelemetryNode::addChildNode(TelemetryNode* childNode)
{
    m_childNodes[childNode->id()] = childNode;
}

void TelemetryNode::removeChildNode(TelemetryNode* childNode)
{
    m_childNodes.remove(childNode->id());
}

