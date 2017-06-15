#ifndef BAROMETRIC_PRESENTER_H
#define BAROMETRIC_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class BarometricPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit BarometricPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::TelemetryMap& parameters) override;
    };
}

#endif // BAROMETRIC_PRESENTER_H
