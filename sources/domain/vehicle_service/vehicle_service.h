#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbEntry;
}

namespace domain
{
    class BaseVehicle;
    class AerialVehicle;

    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(db::DbEntry* entry, QObject* parent = nullptr);
        ~VehicleService() override;

        db::VehicleDescriptionPtrList descriptions() const;
        db::VehicleDescriptionPtr description(int id) const;
        // TODO: fix vehicles search
        db::VehicleDescriptionPtr findDescriptiontByMavId(quint8 mavId) const;
        db::VehicleDescriptionPtr findDescriptiontByName(const QString& name) const;

        BaseVehicle* baseVehicle(const db::VehicleDescriptionPtr& description);
        BaseVehicle* baseVehicle(quint8 mavId);
        AerialVehicle* aerialVehicle(const db::VehicleDescriptionPtr& description);
        AerialVehicle* aerialVehicle(quint8 mavId);

    public slots:
        void saveDescription(const db::VehicleDescriptionPtr& description);
        void removeByDescription(const db::VehicleDescriptionPtr& description);

    signals:
        void vehicleAdded(const db::VehicleDescriptionPtr& description);
        void vehicleRemoved(const db::VehicleDescriptionPtr& description);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_SERVICE_H
