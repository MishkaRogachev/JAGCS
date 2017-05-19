#ifndef DESCRIPTION_VEHICLE_PRESENTER_H
#define DESCRIPTION_VEHICLE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

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
        DescriptionVehiclePresenter(
                domain::VehicleService* service,
                const db::VehicleDescriptionPtr& description,
                QObject* parent = nullptr);

        db::VehicleDescriptionPtr description() const;

    public slots:
        void updateView();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onSetName(const QString& name);
        void onSetMavId(int id);
        void onRemove();

    private:
        domain::VehicleService* const m_service;
        db::VehicleDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_VEHICLE_PRESENTER_H
