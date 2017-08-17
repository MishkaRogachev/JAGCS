#ifndef POWER_SYSTEM_PRESENTER_H
#define POWER_SYSTEM_PRESENTER_H

#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class PowerSystemPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit PowerSystemPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // POWER_SYSTEM_PRESENTER_H
