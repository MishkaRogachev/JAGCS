#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

// Internal
#include "db_traits.h"

namespace data_source
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
        explicit VehicleService(data_source::DbEntry* entry,
                                QObject* parent = nullptr);
        ~VehicleService() override;

        data_source::VehicleDescriptionPtrList descriptions() const;
        data_source::VehicleDescriptionPtr findDescriptiontByMavId(quint8 mavId) const;

        BaseVehicle* baseVehicle(const data_source::VehicleDescriptionPtr& description);
        BaseVehicle* baseVehicle(quint8 mavId);
        AerialVehicle* aerialVehicle(const data_source::VehicleDescriptionPtr& description);
        AerialVehicle* aerialVehicle(quint8 mavId);

    public slots:
        void saveDescription(const data_source::VehicleDescriptionPtr& description);
        void removeByDescription(const data_source::VehicleDescriptionPtr& description);

    signals:
        void vehicleAdded(const data_source::VehicleDescriptionPtr& description);
        void vehicleRemoved(const data_source::VehicleDescriptionPtr& description);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_SERVICE_H
