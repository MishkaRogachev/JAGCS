#ifndef DESCRIPTION_VEHICLE_PRESENTER_H
#define DESCRIPTION_VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace db
{
    class DbFacade;
}

namespace presentation
{
    class DescriptionVehiclePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        DescriptionVehiclePresenter(db::DbFacade* facade, const dao::VehiclePtr& vehicle,
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
        db::DbFacade* const m_facade;
        dao::VehiclePtr m_vehicle;
    };
}

#endif // DESCRIPTION_VEHICLE_PRESENTER_H
