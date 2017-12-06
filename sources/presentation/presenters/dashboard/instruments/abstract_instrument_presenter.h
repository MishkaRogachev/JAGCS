#ifndef ABSTRACT_INSTRUMENT_PRESENTER_H
#define ABSTRACT_INSTRUMENT_PRESENTER_H

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

    private:
        domain::Telemetry* m_node = nullptr;
    };
}

#endif // ABSTRACT_INSTRUMENT_PRESENTER_H
