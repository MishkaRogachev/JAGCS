#ifndef RADIO_STATUS_PRESENTER_H
#define RADIO_STATUS_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "telemetry.h"

namespace presentation
{
    class RadioStatusPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit RadioStatusPresenter(QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::Telemetry::TelemetryMap& parameters);

    protected:
        void connectView(QObject* view) override;

    private:
        domain::Telemetry* m_node;
    };
}

#endif // RADIO_STATUS_PRESENTER_H
