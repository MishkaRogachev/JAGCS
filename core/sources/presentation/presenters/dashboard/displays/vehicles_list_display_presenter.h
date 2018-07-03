#ifndef VEHICLES_LIST_DISPLAY_PRESENTER_H
#define VEHICLES_LIST_DISPLAY_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class VehiclesListDisplayPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VehiclesListDisplayPresenter(QObject* parent = nullptr);
        ~VehiclesListDisplayPresenter() override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLES_LIST_DISPLAY_PRESENTER_H
