#ifndef NAVIGATOR_PRESENTER_H
#define NAVIGATOR_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class NavigatorPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit NavigatorPresenter(domain::Telemetry* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters) override;
    };
}

#endif // NAVIGATOR_PRESENTER_H
