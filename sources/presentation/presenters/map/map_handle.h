#ifndef MAP_HANDLE_H
#define MAP_HANDLE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace presentation
{
    class MapHandle: public QObject
    {
        Q_OBJECT

    public:
        explicit MapHandle(QObject* parent = nullptr);
        ~MapHandle() override;

        dao::MissionPtr selectedMission() const;
        dao::MissionItemPtr selectedMissionItem() const;

    public slots:
        void selectMission(const dao::MissionPtr& mission);
        void selectMissionItem(const dao::MissionItemPtr& item);

    signals:
        // TODO: m_trackingVehicle
        void selectVehicle(const dao::VehiclePtr& vehicle);

        // Signals from map
        void missionSelected(const dao::MissionPtr& mission);
        void missionItemSelected(const dao::MissionItemPtr& item);

        void holded();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MAP_HANDLE_H
