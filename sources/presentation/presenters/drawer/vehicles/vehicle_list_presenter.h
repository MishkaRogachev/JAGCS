#ifndef VEHICLE_LIST_PRESENTER_H
#define VEHICLE_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class VehicleListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VehicleListPresenter(QObject* parent = nullptr);

    public slots:
        void updateVehicles();

        void addVehicle();
        void setAutoAdd(bool add);

    protected:
        void connectView(QObject* view) override;

    private:
        domain::VehicleService* const m_service;
    };
}

#endif // VEHICLE_LIST_PRESENTER_H
