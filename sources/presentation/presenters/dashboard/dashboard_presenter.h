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
        DashboardPresenter(QObject* parent = nullptr);
        ~DashboardPresenter() override;

    public slots:
        void setVehicle(int id);
        void updateInstruments();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // DASHBOARD_PRESENTER_H
