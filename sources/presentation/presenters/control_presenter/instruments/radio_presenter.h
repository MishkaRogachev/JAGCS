#ifndef RADIO_PRESENTER_H
#define RADIO_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class RadioPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit RadioPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // RADIO_PRESENTER_H
