#include "telemetry_node.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_traits.h"

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

QVariant TelemetryNode::parameter(const QString& name) const
{
    return m_parameters.value(name);
}

QVariantMap TelemetryNode::parameters() const
{
    return m_parameters;
}

QStringList TelemetryNode::changedParameters() const
{
    return m_changedParameters;
}

QVariantMap TelemetryNode::takeChangedParameters()
{
    QVariantMap parameters;

    while (!m_changedParameters.isEmpty())
    {
        QString key = m_changedParameters.takeFirst();
        parameters[key] = m_parameters[key];
    }

    return parameters;
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

QList<TelemetryNode*> TelemetryNode::childNodes() const
{
    return m_childNodes.values();
}

void TelemetryNode::setParameter(const QString& name, const QVariant& value)
{
    if (m_parameters.contains(name) && m_parameters[name] == value) return;

    m_parameters[name] = value;
    m_changedParameters.append(name);
}

void TelemetryNode::setParameter(const QStringList& names, const QVariant& value)
{
    if (names.count() > 1)
    {
        TelemetryNode* child = this->childNode(names.at(0));
        child->setParameter(names.at(1), value);
        return;
    }

    if (names.count() == 1) this->setParameter(names.at(0), value);
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
    m_childNodes[childNode->name()] = childNode;
}

void TelemetryNode::removeChildNode(TelemetryNode* childNode)
{
    m_childNodes.remove(childNode->name());
}

