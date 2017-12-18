#ifndef FLIGHT_DISPLAY_PRESENTER_H
#define FLIGHT_DISPLAY_PRESENTER_H

// Internal
#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class FlightDisplayPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit FlightDisplayPresenter(QObject* parent = nullptr);

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateStatus(const domain::Telemetry::TelemetryMap& parameters);
        void updateAhrs(const domain::Telemetry::TelemetryMap& parameters);
        void updateSatellite(const domain::Telemetry::TelemetryMap& parameters);
        void updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters);
        void updatePitot(const domain::Telemetry::TelemetryMap& parameters);
        void updateBarometric(const domain::Telemetry::TelemetryMap& parameters);
        void updateRangefinder(const domain::Telemetry::TelemetryMap& parameters);
        void updateNavigator(const domain::Telemetry::TelemetryMap& parameters);
        void updateHomeAltitude(const domain::Telemetry::TelemetryMap& parameters);
    };
}

#endif // FLIGHT_DISPLAY_PRESENTER_H
