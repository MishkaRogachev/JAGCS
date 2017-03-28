#ifndef FLIGHT_PRESENTER_H
#define FLIGHT_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class MissionService;

    class VehicleService;
    class AbstractVehicle;
}

namespace presentation
{
    class FlightPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        FlightPresenter(domain::MissionService* missionService,
                        domain::VehicleService* vehicleService,
                        QObject* object);
        ~FlightPresenter() override;

    public slots:
        void updateVehicles();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleAdded(domain::AbstractVehicle* vehicle);
        void onVehicleRemoved(domain::AbstractVehicle* vehicle);

        void onVehicleSelected(const QString& vehicleName);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_PRESENTER_H
