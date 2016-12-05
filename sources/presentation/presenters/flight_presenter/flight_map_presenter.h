#ifndef FLIGHT_MAP_PRESENTER_H
#define FLIGHT_MAP_PRESENTER_H

#include "map_presenter.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class FlightMapPresenter: public MapPresenter
    {
        Q_OBJECT

    public:
        explicit FlightMapPresenter(domain::VehicleService* vehicleService,
                                    QObject* parent = nullptr);
        ~FlightMapPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleAdded(uint8_t id);
        void onVehicleRemoved(uint8_t id);

        void onSetHome(const QVariant& position);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_MAP_PRESENTER_H
