#ifndef MAP_PRESENTER_H
#define MAP_PRESENTER_H

#include "base_presenter.h"

namespace domain
{
    class Mission;
    class Vehicle;
}

namespace presentation
{
    class MapPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit MapPresenter(QObject* parent = nullptr);
        ~MapPresenter() override;

    public slots:
        void updateMapViewport();
        void saveMapViewport();

        void addMission(domain::Mission* mission);
        void removeMission(domain::Mission* mission);
        void updateMissionItems();

        void addVehicle(domain::Vehicle* vehicle);
        void removeVehicle(domain::Vehicle* vehicle);

    protected:
        void connectView(QObject* view) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MAP_PRESENTER_H
