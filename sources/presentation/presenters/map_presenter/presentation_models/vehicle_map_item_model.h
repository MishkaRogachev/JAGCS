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
            MarkRole,
            VehicleIdRole,
            TrackRole,
            HomePositionRole
        };

        VehicleMapItemModel(QObject* parent = nullptr);
        ~VehicleMapItemModel() override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void addVehicle(domain::Vehicle* vehicle);
        void removeVehicle(domain::Vehicle* vehicle);

    private slots:
        void onVehicleTypeChanged();
        void onVehicleStateChanged();
        void onVehicleAttitudeChanged();
        void onVehiclePositionChanged();
        void onVehicleHomePositionChanged();

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex vehicleIndex(domain::Vehicle* vehicle) const;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VEHICLE_MAP_ITEM_MODEL_H
