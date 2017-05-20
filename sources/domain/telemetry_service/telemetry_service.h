#ifndef TELEMETRY_SERVICE_H
#define TELEMETRY_SERVICE_H


// Internal
#include "db_traits.h"

#include "status.h"
#include "attitude.h"
#include "position.h"
#include "sns.h"
#include "power_system.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class TelemetryService: public QObject
    {
        Q_OBJECT

    public:
        explicit TelemetryService(db::DbFacade* facade, QObject* parent = nullptr);
        ~TelemetryService() override;

        Status status(int vehicleId) const;
        Attitude attitude(int vehicleId) const;
        Position position(int vehicleId) const;
        Position homePosition(int vehicleId) const;
        Sns sns(int vehicleId) const;
        PowerSystem powerSystem(int vehicleId) const;

    public slots:
        void setStatus(int vehicleId, const Status& status);
        void setAttitude(int vehicleId, const Attitude& attitude);
        void setPosition(int vehicleId, const Position& position);
        void setHomePosition(int vehicleId, const Position& position);
        void setSns(int vehicleId, const Sns& sns);
        void setPowerSystem(int vehicleId, const PowerSystem& powerSystem);

    signals:
        void statusChanged(int vehicleId, Status status);
        void attitudeChanged(int vehicleId, Attitude attitude);
        void positionChanged(int vehicleId, Position position);
        void homePositionChanged(int vehicleId, Position position);
        void snsChanged(int vehicleId, Sns sns);
        void powerSystemChanged(int vehicleId, PowerSystem powerSystem);

    private slots:
         void onVehicleRemoved(const db::VehicleDescriptionPtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TELEMETRY_SERVICE_H
