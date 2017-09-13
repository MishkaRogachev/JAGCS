#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

namespace domain
{
    class MissionService;

    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(MissionService* missionService, QObject* parent = nullptr);
        ~VehicleService() override;

        dao::VehiclePtr vehicle(int id);
        dao::VehiclePtrList vehicles();

        int vehicleIdByMavId(int mavId);
        int mavIdByVehicleId(int id);

    public slots:
        bool save(const dao::VehiclePtr& vehicle);
        bool remove(const dao::VehiclePtr& vehicle);

    signals:
        void vehicleAdded(dao::VehiclePtr vehicle);
        void vehicleRemoved(dao::VehiclePtr vehicle);
        void vehicleChanged(dao::VehiclePtr vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_SERVICE_H
