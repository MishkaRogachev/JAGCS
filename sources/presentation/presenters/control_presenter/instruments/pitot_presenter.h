#ifndef PITOT_PRESENTER_H
#define PITOT_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class PitotPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit PitotPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::TelemetryMap& parameters) override;
    };
}

#endif // PITOT_PRESENTER_H
