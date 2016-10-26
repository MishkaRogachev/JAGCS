#ifndef FLIGHT_MAP_PRESENTER_H
#define FLIGHT_MAP_PRESENTER_H

#include "map_presenter.h"

namespace domain
{
    class Vehicle;
}

namespace presentation
{
    // TODO: routes
    class FlightMapPresenter: public MapPresenter
    {
        Q_OBJECT

    public:
        FlightMapPresenter(QObject* parent = nullptr);
        ~FlightMapPresenter() override;

    public slots:
        void addVehicle(domain::Vehicle* vehicle);
        void removeVehicle(domain::Vehicle* vehicle);

        void updateVehicles();

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // FLIGHT_MAP_PRESENTER_H
