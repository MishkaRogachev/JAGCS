#ifndef VEHICLE_MAP_PRESENTER_H
#define VEHICLE_MAP_PRESENTER_H

#include "map_presenter.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class VehicleMapPresenter: public MapPresenter
    {
        Q_OBJECT

    public:
        explicit VehicleMapPresenter(domain::VehicleService* vehicleService,
                                     QObject* parent = nullptr);
        ~VehicleMapPresenter() override;

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

#endif // VEHICLE_MAP_PRESENTER_H
