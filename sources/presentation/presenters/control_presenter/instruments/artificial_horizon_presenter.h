#ifndef ARTIFICIAL_HORIZON_PRESENTER_H
#define ARTIFICIAL_HORIZON_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace presentation
{
    class ArtificialHorizonPresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit ArtificialHorizonPresenter(QObject* parent = nullptr);

    public slots:
        void applyParameters(const QVariantMap& parameters) override;
    };
}

#endif // ARTIFICIAL_HORIZON_PRESENTER_H
