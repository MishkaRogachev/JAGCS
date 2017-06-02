#ifndef COMBAT_PRESENTER_H
#define COMBAT_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "db_traits.h"

namespace domain
{
    class DomainEntry;

    class Status;
    class Availables;
    class Attitude;
    class Sns;
}

namespace presentation
{
    class CombatPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit CombatPresenter(domain::DomainEntry* entry, QObject* parent = nullptr);
        ~CombatPresenter() override;

    public slots:
        void updateVehicles();

    protected:
        void connectView(QObject* view) override;

    private slots:
        void onVehicleAdded(const db::VehiclePtr& vehicle);
        void onVehicleRemoved(const db::VehiclePtr& vehicle);
        void onVehicleChanged(const db::VehiclePtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMBAT_PRESENTER_H
