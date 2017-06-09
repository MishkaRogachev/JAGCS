#ifndef AHRS_PRESENTER_H
#define AHRS_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class AhrsPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit AhrsPresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const QVariantMap& parameters) override;
    };
}

#endif // AHRS_PRESENTER_H
