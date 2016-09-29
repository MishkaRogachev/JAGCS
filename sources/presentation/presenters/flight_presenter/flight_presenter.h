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

        Q_PROPERTY(QStringList vehicles READ vehicles NOTIFY vehiclesChanged)

    public:
        FlightPresenter(domain::VehicleService* vehicleService, QObject* view);
        ~FlightPresenter() override;

        QStringList vehicles() const;

    signals:
        void vehiclesChanged();

    private slots:
        void onVehicleAdded(uint8_t id);
        void onVehicleRemoved(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_PRESENTER_H
