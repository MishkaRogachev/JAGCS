#ifndef ABSTRACT_MAP_PRESENTER_H
#define ABSTRACT_MAP_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace presentation
{
    class MapHandle;

    class AbstractMapPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        AbstractMapPresenter(QObject* object = nullptr);

        MapHandle* handle() const;

        virtual double centerLatitude() const = 0;
        virtual double centerLongitude() const = 0;
        virtual float zoomLevel() const = 0;

    public slots:
        virtual void setMapCenter(double latitude, double longitude) = 0;
        virtual void setZoomLevel(float zoomLevel) = 0;

    private slots:
        virtual void selectMissionItem(const dao::MissionItemPtr& item) = 0;
        virtual void selectVehicle(const dao::VehiclePtr& vehicle) = 0;

    protected:
        MapHandle* m_handle;
    };
}

#endif // ABSTRACT_MAP_PRESENTER_H
