#ifndef ABSTRACT_INSTRUMENT_PRESENTER_H
#define ABSTRACT_INSTRUMENT_PRESENTER_H

// Std
#include <functional>

// Internal
#include "base_presenter.h"
#include "telemetry.h"

namespace presentation
{
    class AbstractInstrumentPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit AbstractInstrumentPresenter(QObject* parent = nullptr);

    public slots:
        void setVehicle(int vehicleId);

    protected:
        virtual void connectNode(domain::Telemetry* node) = 0;
        virtual void disconnectNode();

        void chainNode(domain::Telemetry* node,
                       std::function<void(const domain::Telemetry::TelemetryMap&)> f);

    private:
        domain::Telemetry* m_node = nullptr;
    };
}

#endif // ABSTRACT_INSTRUMENT_PRESENTER_H
