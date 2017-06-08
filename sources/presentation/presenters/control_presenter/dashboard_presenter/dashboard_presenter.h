#ifndef DASHBOARD_PRESENTER_H
#define DASHBOARD_PRESENTER_H

// Internal
#include "base_presenter.h"

// Qt
#include <QMap>

namespace domain
{
    class TelemetryNode;
}

namespace presentation
{
    class AbstractInstrumentPresenter;

    class DashboardPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        DashboardPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void addInstrument(const QString& viewName, AbstractInstrumentPresenter* instrument);

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onParametersChanged(const QVariantMap& parameters);

    private:
        domain::TelemetryNode* m_node;
        QMap<QString, AbstractInstrumentPresenter*> m_instruments;
    };
}

#endif // DASHBOARD_PRESENTER_H
