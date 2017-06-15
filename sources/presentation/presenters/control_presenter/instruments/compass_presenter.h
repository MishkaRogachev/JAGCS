#ifndef COMPASS_PRESENTER_H
#define COMPASS_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class CompassPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit CompassPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::TelemetryMap& parameters) override;
    };
}

#endif // COMPASS_PRESENTER_H
