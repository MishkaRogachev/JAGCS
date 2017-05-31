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

QStringList TelemetryNode::parameters() const
{
    return m_parameters.keys();
}

QVariantList TelemetryNode::values() const
{
    return m_parameters.values();
}

QVariant TelemetryNode::value(const QString& parameter) const
{
    return m_parameters.value(parameter);
}

QVariant TelemetryNode::value(const QStringList& path) const
{
    if (path.isEmpty()) return QVariant();

    if (path.length() > 1)
    {
        QStringList rPath = path;
        QString key = rPath.takeFirst();
        if (m_childNodes.contains(key)) m_childNodes[key]->value(rPath);
    }
    else return this->value(path.first());
}

TelemetryNode* TelemetryNode::parentNode() const
{
    return m_parentNode;
}

TelemetryNode* TelemetryNode::childNode(const QString& name)
{
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

void TelemetryNode::setValue(const QString& parameter, const QVariant& value)
{
    if (!m_parameters.contains(parameter) ||
        m_parameters.value(parameter) == value) return;

    m_parameters[parameter] = value;

    emit parameterChanged(parameter, value);
    emit parameterChanged({ parameter }, value);
}

void TelemetryNode::setValue(const QStringList& path, const QVariant& value)
{
    if (path.isEmpty()) return;

    if (path.length() > 1)
    {
        QStringList rPath = path;
        QString key = rPath.takeFirst();
        if (m_childNodes.contains(key)) m_childNodes[key]->setValue(rPath, value);
    }
    else this->setValue(path.first(), value);
}

void TelemetryNode::addChildNode(TelemetryNode* childNode)
{
    connect(childNode, QOverload<const QStringList&, const QVariant&>::of(
                &TelemetryNode::parameterChanged),
            this, &TelemetryNode::onChildParameterChanged);

    m_childNodes[childNode->name()] = childNode;
}

void TelemetryNode::removeChildNode(TelemetryNode* childNode)
{
    disconnect(childNode, 0, this, 0);

    m_childNodes.remove(childNode->name());
}

void TelemetryNode::onChildParameterChanged(const QStringList& path, const QVariant& value)
{
    QStringList rPath = path;
    rPath.prepend(m_name);

    emit parameterChanged(rPath, value);
}
