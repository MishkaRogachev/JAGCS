#ifndef VEHICLE_DISPLAY_PRESENTER_H
#define VEHICLE_DISPLAY_PRESENTER_H

// Internal
#include "control_display_presenter.h"

namespace presentation
{
    class VehicleDisplayPresenter: public ControlDisplayPresenter
    {
        Q_OBJECT

    public:
        explicit VehicleDisplayPresenter(QObject* parent = nullptr);

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateAhrs(const domain::Telemetry::TelemetryMap& parameters);
        void updateSatellite(const domain::Telemetry::TelemetryMap& parameters);
        void updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters);
        void updateBarometric(const domain::Telemetry::TelemetryMap& parameters);
        void updateHomeAltitude(const domain::Telemetry::TelemetryMap& parameters);
    };
}

#endif // VEHICLE_DISPLAY_PRESENTER_H
