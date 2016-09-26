#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

#include <QObject>

namespace domain
{
    class Vehicle;

    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(QObject* parent = nullptr);
        ~VehicleService() override;

        Vehicle* vehicle(uint8_t id) const;
        uint8_t vehileId(Vehicle* vehicle) const;

    public slots:
        void removeVehicle(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VEHICLE_SERVICE_H
