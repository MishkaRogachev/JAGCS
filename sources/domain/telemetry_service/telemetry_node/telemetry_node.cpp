#include "telemetry_node.h"

using namespace domain;

TelemetryNode::TelemetryNode(const QString& name, TelemetryNode* parentNode):
    QObject(parentNode),
    m_name(name),
    m_parentNode(parentNode)
{
    if (parentNode) parentNode->addChildNode(this);
}

TelemetryNode::~TelemetryNode()
{
    if (m_parentNode) m_parentNode->removeChildNode(this);
}

QString TelemetryNode::name() const
{
    return m_name;
}

QVariant TelemetryNode::parameter(const QString& parameter) const
{
    return m_parameters.value(parameter);
}

QVariantMap TelemetryNode::parameters() const
{
    return m_parameters;
}

TelemetryNode* TelemetryNode::parentNode() const
{
    return m_parentNode;
}

TelemetryNode* TelemetryNode::childNode(const QString& name)
{
    if (!m_childNodes.contains(name))
    {
        new TelemetryNode(name, this);
    }

    return m_childNodes.value(name, nullptr);
}

TelemetryNode* TelemetryNode::childNode(const QStringList& path)
{
    if (path.isEmpty()) return this;

    QStringList rPath = path;
    TelemetryNode* child = this->childNode(rPath.takeFirst());

    if (!child) return nullptr;
    if (rPath.isEmpty()) return child;

    return child->childNode(rPath);
}

void TelemetryNode::setParameters(const QVariantMap& parameters)
{
    bool changed = false;

    for (const QString& key: parameters.keys())
    {
        if (m_parameters.contains(key) && m_parameters[key] == parameters[key]) continue;

        m_parameters[key] = parameters[key];
        changed = true;
    }

    if (changed) emit parametersChanged(parameters);
}

void TelemetryNode::addChildNode(TelemetryNode* childNode)
{
    m_childNodes[childNode->name()] = childNode;
}

void TelemetryNode::removeChildNode(TelemetryNode* childNode)
{
    m_childNodes.remove(childNode->name());
}
