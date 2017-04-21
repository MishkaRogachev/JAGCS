#ifndef FLIGHT_PRESENTER_H
#define FLIGHT_PRESENTER_H

// Internal
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
        FlightPresenter(domain::VehicleService* vehicleService,
                        QObject* object);
        ~FlightPresenter() override;

    public slots:
        void updateVehicles();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleSelected(const QString& vehicleName);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // FLIGHT_PRESENTER_H
