#ifndef ABSTRACT_DISPLAY_PRESENTER_H
#define ABSTRACT_DISPLAY_PRESENTER_H

// Std
#include <functional>

// Internal
#include "base_presenter.h"
#include "telemetry.h"

namespace presentation
{
    class AbstractDisplayPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit AbstractDisplayPresenter(QObject* parent = nullptr);

        int vehicleId() const;

    public slots:
        void setVehicle(int vehicleId);

    protected:
        virtual void connectNode(domain::Telemetry* node) = 0;
        virtual void disconnectNode();

        void chainNode(domain::Telemetry* node,
                       std::function<void(const domain::Telemetry::TelemetryMap&)> f);

    private:
        int m_vehicleId = 0;
        domain::Telemetry* m_node = nullptr;
    };
}

#endif // ABSTRACT_DISPLAY_PRESENTER_H
