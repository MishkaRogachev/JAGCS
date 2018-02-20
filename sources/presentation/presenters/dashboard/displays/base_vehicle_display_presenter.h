#ifndef BASE_VEHICLE_DISPLAY_PRESENTER_H
#define BASE_VEHICLE_DISPLAY_PRESENTER_H

// Internal
#include "common_vehicle_display_presenter.h"

namespace presentation
{
    class VibrationModel;

    class BaseVehicleDisplayPresenter: public CommonVehicleDisplayPresenter
    {
        Q_OBJECT

    public:
        explicit BaseVehicleDisplayPresenter(QObject* parent = nullptr);

    protected:
        void connectView(QObject* view) override;
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateAhrs(const domain::Telemetry::TelemetryMap& parameters);
        void updateCompass(const domain::Telemetry::TelemetryMap& parameters);
        void updateSatellite(const domain::Telemetry::TelemetryMap& parameters);
        void updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters);
        void updateBattery(const domain::Telemetry::TelemetryMap& parameters);
        void updatePosition(const domain::Telemetry::TelemetryMap& parameters);
        void updateHome(const domain::Telemetry::TelemetryMap& parameters);

    private:
        VibrationModel* m_vibrationModel;
    };
}

#endif // BASE_VEHICLE_DISPLAY_PRESENTER_H
