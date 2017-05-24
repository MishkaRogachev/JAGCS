#ifndef VEHICLE_PRESENTER_H
#define VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class Status;
    class Availables;
    class Attitude;
    class Sns;
}

namespace presentation
{
    class VehiclePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VehiclePresenter(const db::VehiclePtr& vehicle, QObject* parent = nullptr);

    public slots:
        void updateVehicle();

        void setOnline(bool online);
        void setStatus(const domain::Status& status);
        void setAvailables(const domain::Availables& availables);
        void setAttitude(const domain::Attitude& attitude);
        void setSns(const domain::Sns& sns);

    protected:
        void connectView(QObject* view) override;

    private:
        db::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_PRESENTER_H
