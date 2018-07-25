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
            VehicleIdRole = Qt::UserRole + 1,
            VehicleNameRole,
            VehicleTypeRole,
            VehicleOnlineRole,
            CoordinateRole,
            HomeCoordinateRole,
            TargetCoordinateRole,
            HeadingRole,
            CourseRole,
            GroundspeedRole,
            SnsFixRole,
            HdopRadiusRole,
            TrackRole
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
        void onVehicleChanged(const dto::VehiclePtr& vehicle);

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex vehicleIndex(int vehicleId) const;

    private slots:
        void onPositionParametersChanged(
                int vehicleId, const data_source::Telemetry::TelemetryMap& parameters);
        void onHomeParametersChanged(
                int vehicleId, const data_source::Telemetry::TelemetryMap& parameters);
        void onTargetParametersChanged(
                int vehicleId, const data_source::Telemetry::TelemetryMap& parameters);
        void onAhrsParametersChanged(
                int vehicleId, const data_source::Telemetry::TelemetryMap& parameters);
        void onSatelliteParametersChanged(
                int vehicleId, const data_source::Telemetry::TelemetryMap& parameters);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_MAP_ITEM_MODEL_H
