#ifndef VEHICLES_LIST_PRESENTER_H
#define VEHICLES_LIST_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class VehiclesListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VehiclesListPresenter(QObject* parent = nullptr);

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

#endif // VEHICLES_LIST_PRESENTER_H
