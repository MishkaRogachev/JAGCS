#ifndef VEHICLE_DISPLAY_PRESENTER_H
#define VEHICLE_DISPLAY_PRESENTER_H

// Internal
#include "common_vehicle_display_presenter.h"

namespace presentation
{
    class VibrationModel;

    class VehicleDisplayPresenter: public CommonVehicleDisplayPresenter
    {
        Q_OBJECT

    public:
        explicit VehicleDisplayPresenter(QObject* parent = nullptr);

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateAhrs(const domain::Telemetry::TelemetryMap& parameters);
        void updateCompass(const domain::Telemetry::TelemetryMap& parameters);
        void updateEkf(const domain::Telemetry::TelemetryMap& parameters);
        void updateSatellite(const domain::Telemetry::TelemetryMap& parameters);
        void updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters);
        void updateBattery(const domain::Telemetry::TelemetryMap& parameters);
        void updatePitot(const domain::Telemetry::TelemetryMap& parameters);
        void updateBarometric(const domain::Telemetry::TelemetryMap& parameters);
        void updateRadalt(const domain::Telemetry::TelemetryMap& parameters);
        void updatePosition(const domain::Telemetry::TelemetryMap& parameters);
        void updateHome(const domain::Telemetry::TelemetryMap& parameters);
        void updateFlightControl(const domain::Telemetry::TelemetryMap& parameters);
        void updateNavigator(const domain::Telemetry::TelemetryMap& parameters);
        void updateWind(const domain::Telemetry::TelemetryMap& parameters);

    protected:
        void connectView(QObject* view) override;

        VibrationModel* m_vibrationModel;
    };
}

#endif // VEHICLE_DISPLAY_PRESENTER_H
