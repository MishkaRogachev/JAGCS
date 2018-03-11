#ifndef VEHICLE_PRESENTER_H
#define VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class VehiclePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VehiclePresenter(QObject* parent = nullptr);

        Q_INVOKABLE bool checkMavId(int mavId);

    public slots:
        void setVehicle(int id);
        void updateView();
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        domain::VehicleService* const m_service;
        dto::VehiclePtr m_vehicle;
    };
}

#endif // VEHICLE_PRESENTER_H
