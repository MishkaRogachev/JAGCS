#include "abstract_instrument_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

AbstractInstrumentPresenter::AbstractInstrumentPresenter(domain::Telemetry* node,
                                                         QObject* parent):
    BasePresenter(parent),
    m_node(node)
{
    connect(node, &domain::Telemetry::parametersChanged,
            this, &AbstractInstrumentPresenter::onParametersChanged);
}

void AbstractInstrumentPresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->onParametersChanged(m_node->parameters());
}

