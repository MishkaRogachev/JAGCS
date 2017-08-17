#ifndef COMPASS_PRESENTER_H
#define COMPASS_PRESENTER_H

#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class CompassPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit CompassPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // COMPASS_PRESENTER_H
