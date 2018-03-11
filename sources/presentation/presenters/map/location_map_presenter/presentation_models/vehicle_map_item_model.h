#ifndef VEHICLE_MAP_ITEM_MODEL_H
#define VEHICLE_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dto_traits.h"
#include "telemetry.h"

namespace domain
{
    class TelemetryService;
    class VehicleService;
    class Position;
    class Sns;
}

namespace presentation
{
    class VehicleMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            CoordinateRole = Qt::UserRole + 1,
            HeadingRole,
            CourseRole,
            GroundspeedRole,
            SnsFixRole,
            TypeRole,
            VehicleIdRole,
            MavIdRole,
            TrackRole,
            HdopRadius,
            TargetCoordinateRole
        };

        VehicleMapItemModel(domain::VehicleService* vehicleService,
                            domain::TelemetryService* telemetryService,
                            QObject* parent = nullptr);
        ~VehicleMapItemModel() override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void onVehicleAdded(const dto::VehiclePtr& vehicle);
        void onVehicleRemoved(const dto::VehiclePtr& vehicle);

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex vehicleIndex(int vehicleId) const;

    private slots:
        void onPositionParametersChanged(
                int vehicleId, const domain::Telemetry::TelemetryMap& parameters);
        void onAhrsParametersChanged(
                int vehicleId, const domain::Telemetry::TelemetryMap& parameters);
        void onSatelliteParametersChanged(
                int vehicleId, const domain::Telemetry::TelemetryMap& parameters);
        void onTargetParametersChanged(
                int vehicleId, const domain::Telemetry::TelemetryMap& parameters);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_MAP_ITEM_MODEL_H
