#ifndef STATUS_PRESENTER_H
#define STATUS_PRESENTER_H

#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class StatusPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit StatusPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // STATUS_PRESENTER_H
