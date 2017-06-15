#ifndef BAROMETRIC_PRESENTER_H
#define BAROMETRIC_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class BarometricPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit BarometricPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // BAROMETRIC_PRESENTER_H
