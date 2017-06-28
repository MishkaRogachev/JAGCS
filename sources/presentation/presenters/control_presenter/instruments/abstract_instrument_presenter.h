#ifndef ABSTRACT_INSTRUMENT_PRESENTER_H
#define ABSTRACT_INSTRUMENT_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "telemetry.h"

namespace presentation
{
    class AbstractInstrumentPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        AbstractInstrumentPresenter(domain::Telemetry* node, QObject* parent);

    public slots:
        virtual void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) = 0;

    protected:
        void connectView(QObject* view) override;

        domain::Telemetry* m_node;
    };
}

#endif // ABSTRACT_INSTRUMENT_PRESENTER_H
