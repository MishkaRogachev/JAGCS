#ifndef GENERIC_PRESENTER_H
#define GENERIC_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class GenericPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit GenericPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const QVariantMap& parameters) override;
    };
}

#endif // GENERIC_PRESENTER_H
