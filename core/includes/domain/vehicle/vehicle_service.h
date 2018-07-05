#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"

namespace domain
{
    class MissionService;

    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(MissionService* missionService, QObject* parent = nullptr);
        ~VehicleService() override;

        dto::VehiclePtr vehicle(int vehicleId) const;
        dto::VehiclePtrList vehicles() const;

        int vehicleIdByMavId(int mavId) const;
        int mavIdByVehicleId(int vehicleId) const;

        QList<int> employedMavIds() const;

    public slots:
        bool save(const dto::VehiclePtr& vehicle);
        bool remove(const dto::VehiclePtr& vehicle);
        bool addNewVehicle();

    signals:
        void vehicleAdded(dto::VehiclePtr vehicle);
        void vehicleRemoved(dto::VehiclePtr vehicle);
        void vehicleChanged(dto::VehiclePtr vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_SERVICE_H
