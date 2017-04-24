#ifndef VEHICLES_PRESENTER_H
#define VEHICLES_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class VehicleService;
}

namespace presentation
{
    class VehiclesPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VehiclesPresenter(domain::VehicleService* service,
                          QObject* parent = nullptr);
        ~VehiclesPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleAdded(const db::VehicleDescriptionPtr& vehicle);
        void onVehicleRemoved(const db::VehicleDescriptionPtr& vehicle);
        void updateVehicles();

        void onAddVehicle();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLES_PRESENTER_H
