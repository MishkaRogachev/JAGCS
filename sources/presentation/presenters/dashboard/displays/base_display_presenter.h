#ifndef BASE_DISPLAY_PRESENTER_H
#define BASE_DISPLAY_PRESENTER_H

// Internal
#include "base_presenter.h"

namespace presentation
{
    class BaseDisplayPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit BaseDisplayPresenter(QObject* parent = nullptr);

        int vehicleId() const;

    public slots:
        virtual void setVehicle(int vehicleId);

    private:
        int m_vehicleId = 0;
    };
}

#endif // BASE_DISPLAY_PRESENTER_H
