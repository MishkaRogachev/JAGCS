#ifndef FLIGHT_PRESENTER_H
#define FLIGHT_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class FlightPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        FlightPresenter(domain::VehicleService* vehicleService, QObject* view);
        ~FlightPresenter() override;

    public slots:
        void updateVehicles();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleAdded(uint8_t id);
        void onVehicleRemoved(uint8_t id);

        void onVehicleSelected(const QString& vehicleName);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_PRESENTER_H
