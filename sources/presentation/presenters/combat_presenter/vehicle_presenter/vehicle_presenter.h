#ifndef VEHICLE_PRESENTER_H
#define VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class TelemetryNode;
}

namespace presentation
{
    class VehiclePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VehiclePresenter(domain::TelemetryNode* node, const db::VehiclePtr& vehicle,
                         QObject* parent = nullptr);

    public slots:
        void updateVehicle();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onParametersChanged(const QVariantMap& parameters);
        void onSnsParametersChanged(const QVariantMap& parameters);

    private:
        domain::TelemetryNode* m_node;
        db::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_PRESENTER_H
