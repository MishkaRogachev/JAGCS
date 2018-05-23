#ifndef ABSTRACT_MAP_PRESENTER_H
#define ABSTRACT_MAP_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

namespace domain
{
    class CommandService;
}

namespace presentation
{
    class AbstractMapPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        AbstractMapPresenter(QObject* object = nullptr);
        ~AbstractMapPresenter() override;

        virtual double centerLatitude() const = 0;
        virtual double centerLongitude() const = 0;
        virtual float zoomLevel() const = 0;

    public slots:
        virtual void setMapCenter(double latitude, double longitude) = 0;
        virtual void setZoomLevel(float zoomLevel) = 0;

        void moveItem(int itemId, double latitude, double longitude);
        void navTo(int vehicleId, double latitude, double longitude, float altitude);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // ABSTRACT_MAP_PRESENTER_H
