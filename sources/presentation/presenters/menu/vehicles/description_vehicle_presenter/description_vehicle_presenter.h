#ifndef DESCRIPTION_VEHICLE_PRESENTER_H
#define DESCRIPTION_VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class DescriptionVehiclePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        DescriptionVehiclePresenter(domain::VehicleService* service,
                                    const dao::VehiclePtr& vehicle,
                                    QObject* parent = nullptr);

        dao::VehiclePtr vehicle() const;

    public slots:
        void updateView();
        void updateStatus();
        void save();
        void remove();

    protected:
        void connectView(QObject* view) override;

    private:
        domain::VehicleService* const m_service;
        dao::VehiclePtr m_vehicle;
    };
}

#endif // DESCRIPTION_VEHICLE_PRESENTER_H
