#ifndef ABSTRACT_INSTRUMENT_PRESENTER_H
#define ABSTRACT_INSTRUMENT_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class AbstractInstrumentPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit AbstractInstrumentPresenter(QObject* parent = nullptr);

    public slots:
        virtual void applyParameters(const QVariantMap& parameters) = 0;
    };
}

#endif // ABSTRACT_INSTRUMENT_PRESENTER_H
