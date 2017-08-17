#ifndef WIND_PRESENTER_H
#define WIND_PRESENTER_H

#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class WindPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit WindPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // WIND_PRESENTER_H
