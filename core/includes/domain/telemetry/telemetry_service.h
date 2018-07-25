#ifndef TELEMETRY_SERVICE_H
#define TELEMETRY_SERVICE_H

// Internal
#include "dto_traits.h"

namespace data_source
{
    class Telemetry;
}

namespace domain
{
    class VehicleService;

    class TelemetryService: public QObject
    {
        Q_OBJECT

    public:
        explicit TelemetryService(domain::VehicleService* service, QObject* parent = nullptr);
        ~TelemetryService() override;

        QList<data_source::Telemetry*> rootNodes() const;
        data_source::Telemetry* vehicleNode(int vehicleId) const;
        data_source::Telemetry* mavNode(int mavId) const;
        // TODO: multiply radio telemetry
        data_source::Telemetry* radioNode() const;

    private slots:
        void onVehicleAdded(const dto::VehiclePtr& vehicle);
        void onVehicleRemoved(const dto::VehiclePtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TELEMETRY_SERVICE_H
