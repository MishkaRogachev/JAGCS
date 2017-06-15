#ifndef STATUS_PRESENTER_H
#define STATUS_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class StatusPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit StatusPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const domain::TelemetryMap& parameters) override;
    };
}

#endif // STATUS_PRESENTER_H
