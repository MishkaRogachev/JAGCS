#include "abstract_telemetry_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

AbstractTelemetryPresenter::AbstractTelemetryPresenter(domain::Telemetry* node, QObject* parent):
    BaseInstrumentPresenter(parent),
    m_node(node)
{
    connect(node, &domain::Telemetry::parametersChanged,
            this, &AbstractTelemetryPresenter::onParametersChanged);
}

void AbstractTelemetryPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->onParametersChanged(m_node->parameters());
}

