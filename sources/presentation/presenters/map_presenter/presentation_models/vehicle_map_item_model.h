#ifndef VEHICLE_MAP_ITEM_MODEL_H
#define VEHICLE_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "vehicle.h"

namespace presentation
{
    class VehicleMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            PositionRole = Qt::UserRole + 1,
            DirectionRole,
            MarkRole
        };

        VehicleMapItemModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

        QModelIndex vehicleIndex(domain::Vehicle* vehicle) const;

    public slots:
        void addVehicle(domain::Vehicle* vehicle);
        void removeVehicle(domain::Vehicle* vehicle);

    private slots:
        void onVehicleNavigationChanged();
        void onVehicleAttitudeChanged();

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        QList<domain::Vehicle*> m_vehicles;
    };
}

#endif // VEHICLE_MAP_ITEM_MODEL_H
