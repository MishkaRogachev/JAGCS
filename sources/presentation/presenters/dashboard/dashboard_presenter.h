#ifndef DASHBOARD_PRESENTER_H
#define DASHBOARD_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class DashboardPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        enum Display
        {
            ShortVehicleDisplay,
            FixedWingVehicleDisplay,
            RotarityWingVehicleDisplay,
        };

        DashboardPresenter(QObject* parent = nullptr);
        ~DashboardPresenter() override;

    protected:
        void connectView(QObject* view);

    private:
        class Impl;
        QScopedPointer<Impl> const d;

        Q_ENUM(Display)
    };
}

#endif // DASHBOARD_PRESENTER_H
