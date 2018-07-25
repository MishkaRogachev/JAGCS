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
        void connectNode(data_source::Telemetry* node) override;

    private slots:
        void updateEkf(const data_source::Telemetry::TelemetryMap& parameters);
        void updatePitot(const data_source::Telemetry::TelemetryMap& parameters);
        void updateBarometric(const data_source::Telemetry::TelemetryMap& parameters);
        void updateRadalt(const data_source::Telemetry::TelemetryMap& parameters);
        void updateFlightControl(const data_source::Telemetry::TelemetryMap& parameters);
        void updateNavigator(const data_source::Telemetry::TelemetryMap& parameters);
        void updateLandingSystem(const data_source::Telemetry::TelemetryMap& parameters);
        void updateWind(const data_source::Telemetry::TelemetryMap& parameters);
    };
}

#endif // AERIAL_VEHICLE_DISPLAY_PRESENTER_H
