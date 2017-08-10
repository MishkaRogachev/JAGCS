#include "telemetry_portion.h"

using namespace domain;

TelemetryPortion::TelemetryPortion(Telemetry* node):
    QObject(nullptr),
    m_node(node)
{
    if (node)
    {
        connect(this, &TelemetryPortion::setParameter,
                node, QOverload< const QList< Telemetry::TelemetryId >&,
                const QVariant& > ::of(&Telemetry::setParameter));
    }
}

TelemetryPortion::~TelemetryPortion()
{
    if (m_node)
    {
        QMetaObject::invokeMethod(m_node, "notify", Qt::QueuedConnection);
    }
}
