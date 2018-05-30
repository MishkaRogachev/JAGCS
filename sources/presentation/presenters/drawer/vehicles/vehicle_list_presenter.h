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
        ~VehicleListPresenter() override;

    public slots:
        void addVehicle();
        void setAutoAdd(bool add);
        void filter(const QString& filterString);

    protected:
        void connectView(QObject* view) override;

    private:
         class Impl;
         QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_LIST_PRESENTER_H
