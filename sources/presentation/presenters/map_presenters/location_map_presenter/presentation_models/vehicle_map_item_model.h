#ifndef VEHICLE_MAP_ITEM_MODEL_H
#define VEHICLE_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "db_traits.h"

namespace domain
{
    class VehicleService;
    class BaseVehicle;
}

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
            HdopRadius
        };

        VehicleMapItemModel(domain::VehicleService* vehicleService,
                            QObject* parent = nullptr);
        ~VehicleMapItemModel() override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void onVehicleAdded(const db::VehicleDescriptionPtr& description);
        void onVehicleRemoved(const db::VehicleDescriptionPtr& description);

    private slots:
        void onVehicleStateChanged();
        void onVehicleAttitudeChanged();
        void onVehiclePositionChanged();
        void onVehicleGpsChanged();

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex vehicleIndex(domain::BaseVehicle* vehicle) const;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VEHICLE_MAP_ITEM_MODEL_H
