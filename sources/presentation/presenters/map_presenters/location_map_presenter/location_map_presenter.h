#ifndef LOCATION_MAP_PRESENTER_H
#define LOCATION_MAP_PRESENTER_H

// Internal
#include "abstract_map_presenter.h"

namespace domain
{
    class DomainEntry;
}

namespace presentation
{
    class LocationMapPresenter: public AbstractMapPresenter
    {
        Q_OBJECT

    public:
        explicit LocationMapPresenter(domain::DomainEntry* entry, QObject* object = nullptr);
        ~LocationMapPresenter() override;

        double centerLatitude() const override;
        double centerLongitude() const override;
        float zoomLevel() const override;

    public slots:
        void setMapCenter(double latitude, double longitude) override;
        void setZoomLevel(float zoomLevel) override;

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // LOCATION_MAP_PRESENTER_H
