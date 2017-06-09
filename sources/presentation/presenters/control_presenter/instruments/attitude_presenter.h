#ifndef ATTITUDE_PRESENTER_H
#define ATTITUDE_PRESENTER_H

#include "abstract_instrument_presenter.h"

namespace domain
{
    class TelemetryNode;
}

namespace presentation
{
    class AttitudePresenter: public AbstractInstrumentPresenter
    {
        Q_OBJECT

    public:
        explicit AttitudePresenter(domain::TelemetryNode* node, QObject* parent = nullptr);

    public slots:
        void onParametersChanged(const QVariantMap& parameters) override;

    protected:
        void connectView(QObject* view) override;

    private:
        domain::TelemetryNode* m_node;
    };
}

#endif // ATTITUDE_PRESENTER_H
