#ifndef TELEMETRY_SERVICE_H
#define TELEMETRY_SERVICE_H

// Internal
#include "dao_traits.h"

namespace domain
{
    class VehicleService;
    class Telemetry;

    class TelemetryService: public QObject
    {
        Q_OBJECT

    public:
        explicit TelemetryService(domain::VehicleService* service,
                                  QObject* parent = nullptr);
        ~TelemetryService() override;

        QList<Telemetry*> rootNodes() const;
        Telemetry* vehicleNode(int vehicleId) const;
        Telemetry* mavNode(int mavId) const;
        // TODO: multiply radio telemetry
        Telemetry* radioNode() const;

    private slots:
        void onVehicleAdded(const dao::VehiclePtr& vehicle);
        void onVehicleRemoved(const dao::VehiclePtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TELEMETRY_SERVICE_H
