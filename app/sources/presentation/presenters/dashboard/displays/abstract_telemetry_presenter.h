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
        void setNode(data_source::Telemetry* node);

    protected:
        virtual void connectNode(data_source::Telemetry* node) = 0;
        virtual void disconnectNode();

        void chainNode(data_source::Telemetry* node,
                       std::function<void(const data_source::Telemetry::TelemetryMap&)> func);

    private:
        data_source::Telemetry* m_node = nullptr;
    };
}

#endif // ABSTRACT_TELEMETRY_PRESENTER_H
