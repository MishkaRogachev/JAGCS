#ifndef DASHBOARD_PRESENTER_H
#define DASHBOARD_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class TelemetryNode;
}

namespace presentation
{
    class DashboardPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        DashboardPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onParametersChanged(const QVariantMap& parameters);

    private:
        domain::TelemetryNode* m_node;
    };
}

#endif // DASHBOARD_PRESENTER_H
