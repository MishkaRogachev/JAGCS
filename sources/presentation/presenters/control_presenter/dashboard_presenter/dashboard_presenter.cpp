#include "dashboard_presenter.h"

// Qt
#include <QVariant>

// Internal
#include "telemetry.h"

using namespace presentation;

DashboardPresenter::DashboardPresenter(domain::TelemetryNode* node, QObject* parent):
    BasePresenter(parent),
    m_node(node)
{
    connect(m_node, &domain::TelemetryNode::parametersChanged,
            this, &DashboardPresenter::onParametersChanged);
}

void DashboardPresenter::connectView(QObject* view)
{
    if (!view) return;

    this->onParametersChanged(m_node->parameters());
}

void DashboardPresenter::onParametersChanged(const QVariantMap& parameters)
{
    // TODO:
}

