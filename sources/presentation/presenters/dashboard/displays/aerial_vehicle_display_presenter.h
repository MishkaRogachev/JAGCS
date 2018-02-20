#ifndef AERIAL_VEHICLE_DISPLAY_PRESENTER_H
#define AERIAL_VEHICLE_DISPLAY_PRESENTER_H

// Internal
#include "base_vehicle_display_presenter.h"

namespace presentation
{
    class AerialVehicleDisplayPresenter: public BaseVehicleDisplayPresenter
    {
        Q_OBJECT

    public:
        explicit AerialVehicleDisplayPresenter(QObject* parent = nullptr);

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateEkf(const domain::Telemetry::TelemetryMap& parameters);
        void updatePitot(const domain::Telemetry::TelemetryMap& parameters);
        void updateBarometric(const domain::Telemetry::TelemetryMap& parameters);
        void updateRadalt(const domain::Telemetry::TelemetryMap& parameters);
        void updateFlightControl(const domain::Telemetry::TelemetryMap& parameters);
        void updateNavigator(const domain::Telemetry::TelemetryMap& parameters);
        void updateWind(const domain::Telemetry::TelemetryMap& parameters);
    };
}

#endif // AERIAL_VEHICLE_DISPLAY_PRESENTER_H
