#ifndef VEHICLES_LIST_DISPLAY_PRESENTER_H
#define VEHICLES_LIST_DISPLAY_PRESENTER_H

// Internal
#include "common_vehicle_display_presenter.h"

namespace presentation
{
    class VehiclesListDisplayPresenter: public CommonVehicleDisplayPresenter
    {
        Q_OBJECT

    public:
        explicit VehiclesListDisplayPresenter(QObject* parent = nullptr);
        ~VehiclesListDisplayPresenter() override;

    public slots:
        void setGlobalPoi(double latitude, double longitude, float altitude);

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLES_LIST_DISPLAY_PRESENTER_H
