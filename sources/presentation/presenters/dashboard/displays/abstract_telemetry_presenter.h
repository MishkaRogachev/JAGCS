#ifndef ABSTRACT_TELEMETRY_PRESENTER_H
#define ABSTRACT_TELEMETRY_PRESENTER_H

// Std
#include <functional>

// Internal
#include "base_presenter.h"
#include "telemetry.h"

namespace presentation
{
    class AbstractTelemetryPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit AbstractTelemetryPresenter(QObject* parent = nullptr);

    public slots:
        void setNode(domain::Telemetry* node);

    protected:
        virtual void connectNode(domain::Telemetry* node);
        virtual void disconnectNode();

        void chainNode(domain::Telemetry* node,
                       std::function<void(const domain::Telemetry::TelemetryMap&)> func);

    private:
        domain::Telemetry* m_node = nullptr;
    };
}

#endif // ABSTRACT_TELEMETRY_PRESENTER_H
