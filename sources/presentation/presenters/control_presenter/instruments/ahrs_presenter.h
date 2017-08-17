#ifndef AHRS_PRESENTER_H
#define AHRS_PRESENTER_H

#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class AhrsPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit AhrsPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // AHRS_PRESENTER_H
