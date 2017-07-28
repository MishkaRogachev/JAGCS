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

        dao::VehiclePtr vehicle(int id, bool reload = false);
        dao::VehiclePtrList vehicles(const QString& condition = QString(), bool reload  = false);

        int vehicleIdByMavId(int mavId) const;

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
