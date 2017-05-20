#ifndef TELEMETRY_SERVICE_H
#define TELEMETRY_SERVICE_H


// Internal
#include "db_traits.h"

#include "attitude.h"
#include "position.h"
#include "sns.h"

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

        Attitude attitude(int vehicleId) const;
        Position position(int vehicleId) const;
        Position homePosition(int vehicleId) const;
        Sns sns(int vehicleId) const;

    public slots:
        void setAttitude(int vehicleId, const Attitude& attitude);
        void setPosition(int vehicleId, const Position& position);
        void setHomePosition(int vehicleId, const Position& position);
        void setSns(int vehicleId, const Sns& sns);

    signals:
        void attitudeChanged(int vehicleId, const Attitude& attitude);
        void positionChanged(int vehicleId, const Position& position);
        void homePositionChanged(int vehicleId, const Position& position);
        void snsChanged(int vehicleId, const Sns& sns);

    private slots:
         void onVehicleRemoved(const db::VehicleDescriptionPtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TELEMETRY_SERVICE_H
