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
        void connectNode(data_source::Telemetry* node) override;

    private slots:
        void updateSystem(const data_source::Telemetry::TelemetryMap& parameters);
        void updateAhrs(const data_source::Telemetry::TelemetryMap& parameters);
        void updateCompass(const data_source::Telemetry::TelemetryMap& parameters);
        void updateSatellite(const data_source::Telemetry::TelemetryMap& parameters);
        void updatePowerSystem(const data_source::Telemetry::TelemetryMap& parameters);
        void updateBattery(const data_source::Telemetry::TelemetryMap& parameters);
        void updatePosition(const data_source::Telemetry::TelemetryMap& parameters);
        void updateHome(const data_source::Telemetry::TelemetryMap& parameters);

    private:
        VibrationModel* m_vibrationModel;
    };
}

#endif // BASE_VEHICLE_DISPLAY_PRESENTER_H
