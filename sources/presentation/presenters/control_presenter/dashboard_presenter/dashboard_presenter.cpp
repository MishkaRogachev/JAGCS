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

DashboardPresenter::~DashboardPresenter()
{
    this->setViewProperty(PROPERTY(instruments), QStringList());
}

void DashboardPresenter::addInstrument(const QString& viewName,
                                       AbstractInstrumentPresenter* instrument)
{
    m_instruments[viewName] = instrument;
}

void DashboardPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(instrumentAdded(QString, QObject*)),
            this, SLOT(onInstrumentAdded(QString, QObject*)));

    this->setViewProperty(PROPERTY(instruments), QStringList(m_instruments.keys()));

    this->onParametersChanged(m_node->parameters());
}

void DashboardPresenter::onInstrumentAdded(const QString& instrument, QObject* view)
{
    if (!m_instruments.contains(instrument)) return;

    m_instruments[instrument]->setView(view);
}

void DashboardPresenter::onParametersChanged(const QVariantMap& parameters)
{
    for (AbstractInstrumentPresenter* instrument: m_instruments.values())
    {
        instrument->applyParameters(parameters);
    }
}

