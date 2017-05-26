#ifndef VEHICLE_PRESENTER_H
#define VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class TelemetryService;

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
        VehiclePresenter(domain::TelemetryService* telemetryService,
                         const db::VehiclePtr& vehicle, QObject* parent = nullptr);

    public slots:
        void updateVehicle();

        void updateOnline(bool online);
        void updateStatus(const domain::Status& status);
        void updateAvailables(const domain::Availables& availables);
        void updateAttitude(const domain::Attitude& attitude);
        void updateSns(const domain::Sns& sns);

    protected:
        void connectView(QObject* view) override;

    private:
        domain::TelemetryService* m_telemetryService;
        db::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_PRESENTER_H
