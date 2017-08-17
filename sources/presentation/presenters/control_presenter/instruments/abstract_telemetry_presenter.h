#ifndef ABSTRACT_TELEMETRY_PRESENTER_H
#define ABSTRACT_TELEMETRY_PRESENTER_H

// Internal
#include "base_instrument_presenter.h"
#include "telemetry.h"

namespace presentation
{
    class AbstractTelemetryPresenter: public BaseInstrumentPresenter
    {
        Q_OBJECT

    public:
        AbstractTelemetryPresenter(domain::Telemetry* node, QObject* parent);

    public slots:
        virtual void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) = 0;

    protected:
        void connectView(QObject* view) override;

        domain::Telemetry* m_node;
    };
}

#endif // ABSTRACT_TELEMETRY_PRESENTER_H
