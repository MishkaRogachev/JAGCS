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
    class Telemetry;

    class TelemetryService: public QObject
    {
        Q_OBJECT

    public:
        explicit TelemetryService(db::DbFacade* facade, QObject* parent = nullptr);
        ~TelemetryService() override;

        QList<Telemetry*> rootNodes() const;
        Telemetry* vehicleNode(int vehicleId) const;
        Telemetry* mavNode(int mavId) const;
        // TODO: multiply radio telemetry
        Telemetry* radioNode() const;

    private slots:
        void onVehicleRemoved(const db::VehiclePtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TELEMETRY_SERVICE_H
