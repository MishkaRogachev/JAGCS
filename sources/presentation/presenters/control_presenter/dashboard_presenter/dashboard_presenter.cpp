#include "dashboard_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "telemetry.h"
#include "abstract_instrument_presenter.h"

using namespace presentation;

DashboardPresenter::DashboardPresenter(domain::TelemetryNode* node, QObject* parent):
    BasePresenter(parent),
    m_node(node)
{
    connect(m_node, &domain::TelemetryNode::parametersChanged,
            this, &DashboardPresenter::onParametersChanged);
}

void DashboardPresenter::addInstrument(const QString& viewName,
                                       AbstractInstrumentPresenter* instrument)
{
    m_instruments[viewName] = instrument;
}

void DashboardPresenter::connectView(QObject* view)
{
    QStringList instruments = m_instruments.keys();
    this->setViewProperty(PROPERTY(instruments), instruments);

    for (const QString& viewName: instruments)
    {
        m_instruments[viewName]->setView(view->findChild<QObject*>(viewName));
    }

    this->onParametersChanged(m_node->parameters());
}

void DashboardPresenter::onParametersChanged(const QVariantMap& parameters)
{
    for (AbstractInstrumentPresenter* instrument: m_instruments.values())
    {
        instrument->applyParameters(parameters);
    }
}

