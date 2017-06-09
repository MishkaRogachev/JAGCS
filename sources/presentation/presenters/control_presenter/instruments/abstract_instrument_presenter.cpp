#include "abstract_instrument_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "telemetry_node.h"

using namespace presentation;

AbstractInstrumentPresenter::AbstractInstrumentPresenter(domain::TelemetryNode* node,
                                                         QObject* parent):
    BasePresenter(parent),
    m_node(node)
{
    connect(node, &domain::TelemetryNode::parametersChanged,
            this, &AbstractInstrumentPresenter::onParametersChanged);
}

void AbstractInstrumentPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->onParametersChanged(m_node->parameters());
}

