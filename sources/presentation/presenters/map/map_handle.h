#ifndef MAP_HANDLE_H
#define MAP_HANDLE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace presentation
{
    class AbstractMapPresenter;

    class MapHandle: public QObject
    {
        Q_OBJECT

    public:
        MapHandle(AbstractMapPresenter* map);

    signals:
        void reloadMap();

        // Signals to map
        void selectMissionItem(const dao::MissionItemPtr& item);
        void selectVehicle(const dao::VehiclePtr& vehicle);

        // Signals from map
        void missionItemSelected(const dao::MissionItemPtr& item);
        void holded();

    private:
        AbstractMapPresenter* const m_map;
    };
}

#endif // MAP_HANDLE_H
