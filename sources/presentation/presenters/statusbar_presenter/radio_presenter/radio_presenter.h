#ifndef RADIO_PRESENTER_H
#define RADIO_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "telemetry.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class RadioPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit RadioPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters);

    protected:
        void connectView(QObject* view) override;

    private:
        domain::Telemetry* m_node;
    };
}

#endif // RADIO_PRESENTER_H
