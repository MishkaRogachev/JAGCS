#ifndef TELEMETRY_SERVICE_H
#define TELEMETRY_SERVICE_H


// Internal
#include "db_traits.h"

#include "attitude.h"

namespace domain
{
    class TelemetryService: public QObject
    {
        Q_OBJECT

    public:
        explicit TelemetryService(QObject* parent = nullptr);
        ~TelemetryService() override;

        Attitude attitude(const db::VehicleDescriptionPtr& vehicle) const;

    public slots:
        void setAttitude(const db::VehicleDescriptionPtr& vehicle, const Attitude& attitude);

    signals:
        void attitudeChanged(const db::VehicleDescriptionPtr& vehicle, const Attitude& attitude);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // TELEMETRY_SERVICE_H
