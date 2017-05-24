#ifndef VEHICLE_PRESENTER_H
#define VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class Attitude;
}

namespace presentation
{
    class VehiclePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VehiclePresenter(const db::VehicleDescriptionPtr& vehicle,
                         QObject* parent = nullptr);

    public slots:
        void updateVehicle();

        void setAttitude(const domain::Attitude& attitude);

    protected:
        void connectView(QObject* view) override;

    private:
        db::VehicleDescriptionPtr m_vehicle;
    };
}

#endif // VEHICLE_PRESENTER_H
