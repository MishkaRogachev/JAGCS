#ifndef ABSTRACT_MAP_PRESENTER_H
#define ABSTRACT_MAP_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class AbstractMapPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        AbstractMapPresenter(QObject* object = nullptr);

        virtual double centerLatitude() const = 0;
        virtual double centerLongitude() const = 0;
        virtual float zoomLevel() const = 0;

    public slots:
        virtual void setMapCenter(double latitude, double longitude) = 0;
        virtual void setZoomLevel(float zoomLevel) = 0;

        virtual void selectMissionItem(const dao::MissionItemPtr& item) = 0;
        virtual void selectVehicle(const dao::VehiclePtr& vehicle) = 0;

    signals:
        void missionItemSelected(const dao::MissionItemPtr& item);
        void holded();
    };
}

#endif // ABSTRACT_MAP_PRESENTER_H
