#ifndef VEHICLE_SERVICE_H
#define VEHICLE_SERVICE_H

// Qt
#include <QObject>

namespace domain
{
    class AbstractVehicle;
    class BaseVehicle;
    class AerialVehicle;

    class VehicleService: public QObject
    {
        Q_OBJECT

    public:
        explicit VehicleService(QObject* parent = nullptr);

        AbstractVehicle* vehicle(int index) const;
        const QList<AbstractVehicle*>& vehicles() const;

        AbstractVehicle* vehicleForId(uint8_t id) const;
        BaseVehicle* baseVehicle(uint8_t id) const;
        AerialVehicle* aerialVehicle(uint8_t id) const;

    public slots:
        void addVehicle(AbstractVehicle* vehicle);
        void createVehicle(uint8_t vehicleId, int type);
        void removeVehicle(AbstractVehicle* vehicle);
        void deleteVehicle(AbstractVehicle* vehicle);

    signals:
        void vehicleAdded(AbstractVehicle* vehicle);
        void vehicleRemoved(AbstractVehicle* vehicle);

    private:
        QList<AbstractVehicle*> m_vehicles;
    };
}

#endif // VEHICLE_SERVICE_H
