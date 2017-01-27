#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

namespace domain
{
    class Vehicle;

    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(QObject* parent = nullptr);

        Vehicle* vehicle(int index) const;

        const QList<Vehicle*>& vehicles() const;

        Vehicle* forceVehicle(uint8_t id);

    public slots:
        void addVehicle(Vehicle* vehicle);
        void removeVehicle(Vehicle* vehicle);
        void deleteVehicle(Vehicle* vehicle);

    signals:
        void vehicleAdded(Vehicle* vehicle);
        void vehicleRemoved(Vehicle* vehicle);

    private:
        QList<Vehicle*> m_vehicles;
    };
}

#endif // VEHICLE_SERVICE_H
