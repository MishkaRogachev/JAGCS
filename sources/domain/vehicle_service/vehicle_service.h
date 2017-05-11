#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class BaseVehicle;
    class AerialVehicle;

    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(db::DbFacade* facade, QObject* parent = nullptr);
        ~VehicleService() override;

        db::VehicleDescriptionPtrList descriptions() const;
        db::VehicleDescriptionPtr description(int id) const;
        // TODO: fix vehicles search
        db::VehicleDescriptionPtr findDescriptionByMavId(quint8 mavId) const;
        db::VehicleDescriptionPtr findDescriptionByName(const QString& name) const;

        BaseVehicle* baseVehicle(const db::VehicleDescriptionPtr& description);
        BaseVehicle* baseVehicle(quint8 mavId);
        AerialVehicle* aerialVehicle(const db::VehicleDescriptionPtr& description);
        AerialVehicle* aerialVehicle(quint8 mavId);

    public slots:
        void saveDescription(const db::VehicleDescriptionPtr& description);
        void removeByDescription(const db::VehicleDescriptionPtr& description);

    signals:
        void vehicleAdded(db::VehicleDescriptionPtr description);
        void vehicleRemoved(db::VehicleDescriptionPtr description);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_SERVICE_H
