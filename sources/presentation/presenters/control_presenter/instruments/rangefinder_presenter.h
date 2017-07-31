#ifndef RANGEFINDER_PRESENTER_H
#define RANGEFINDER_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class RangefinderPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit RangefinderPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // RANGEFINDER_PRESENTER_H
