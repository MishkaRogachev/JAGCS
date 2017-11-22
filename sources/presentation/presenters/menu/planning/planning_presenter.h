#ifndef PLANNING_PRESENTER_H
#define PLANNING_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class PlanningPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit PlanningPresenter(QObject* parent = nullptr);

    public slots:
        void updateVehicles();

    private:
        domain::VehicleService* const m_service;
    };
}

#endif // PLANNING_PRESENTER_H
