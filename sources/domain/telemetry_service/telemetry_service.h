#ifndef TELEMETRY_SERVICE_H
#define TELEMETRY_SERVICE_H

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class TelemetryNode;

    class TelemetryService: public QObject
    {
        Q_OBJECT

    public:
        explicit TelemetryService(db::DbFacade* facade, QObject* parent = nullptr);
        ~TelemetryService() override;

        TelemetryNode* node(int vehicleId) const;
        TelemetryNode* nodeByMavId(int mavId) const;

    private slots:
        void onVehicleAdded(const db::VehiclePtr& vehicle);
        void onVehicleRemoved(const db::VehiclePtr& vehicle);

    signals:
        void nodeAdded(domain::TelemetryNode* node);
        void nodeRemoved(domain::TelemetryNode* node);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TELEMETRY_SERVICE_H
