#ifndef SATELLITE_PRESENTER_H
#define SATELLITE_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class SatellitePresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit SatellitePresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::TelemetryMap& parameters) override;
    };
}

#endif // SATELLITE_PRESENTER_H
