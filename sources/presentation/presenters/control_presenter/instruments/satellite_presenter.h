#ifndef SATELLITE_PRESENTER_H
#define SATELLITE_PRESENTER_H

#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class SatellitePresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit SatellitePresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // SATELLITE_PRESENTER_H
