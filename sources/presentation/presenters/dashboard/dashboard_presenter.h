#ifndef DASHBOARD_PRESENTER_H
#define DASHBOARD_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class DashboardPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        enum Instrument // TODO: instruments to dao type - differet instruments for different vehicles
        {
            SatelliteDispaly,
            FlightDisplay,
            NavigationDisplay,
            ControlDisplay,
            MissionDisplay
        };

        DashboardPresenter(QObject* parent = nullptr);
        ~DashboardPresenter() override;

    public slots:
        void setVehicle(int id);
        void updateVehicle();

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        Q_ENUM(Instrument)
    };
}

#endif // DASHBOARD_PRESENTER_H
