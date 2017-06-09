#ifndef ABSTRACT_INSTRUMENT_PRESENTER_H
#define ABSTRACT_INSTRUMENT_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class TelemetryNode;
}

namespace presentation
{
    class AbstractInstrumentPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        AbstractInstrumentPresenter(domain::TelemetryNode* node, QObject* parent);

    public slots:
        virtual void onParametersChanged(const QVariantMap& parameters) = 0;

    protected:
        void connectView(QObject* view) override;

        domain::TelemetryNode* m_node;
    };
}

#endif // ABSTRACT_INSTRUMENT_PRESENTER_H
