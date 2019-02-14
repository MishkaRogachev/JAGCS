#ifndef SWARM_MAP_ITEM_MODEL_H
#define SWARM_MAP_ITEM_MODEL_H

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
    class SwarmMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum SwarmMapItemRoles
        {
            SwarmPoiCoordinateRole,
            SwarmPoiGroupRole,
            SwarmPoiNumberRole,
            SwarmPoiConfirmed
        };

        SwarmMapItemModel(domain::TelemetryService* telemetryService, QObject* parent = nullptr);
        ~SwarmMapItemModel() override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private slots:
        void onSwarmPoiParametersChanged(const domain::Telemetry::TelemetryMap& parameters);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // SWARM_MAP_ITEM_MODEL_H
