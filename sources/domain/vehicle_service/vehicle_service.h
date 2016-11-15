#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

namespace domain
{
    class Vehicle;

    // TODO: service layer
    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(QObject* parent = nullptr);
        ~VehicleService() override;

        Vehicle* vehicle(uint8_t id) const;
        uint8_t vehileId(Vehicle* vehicle) const;
        QList<Vehicle*> vehicles() const;
        QList<uint8_t> vehileIds() const;

        Vehicle* requestVehicle(uint8_t id);

    public slots:
        void removeVehicle(uint8_t id);

    signals:
        void vehicleAdded(uint8_t id);
        void vehicleRemoved(uint8_t id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VEHICLE_SERVICE_H
