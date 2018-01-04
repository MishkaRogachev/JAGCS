#ifndef VEHICLE_DISPLAY_PRESENTER_H
#define VEHICLE_DISPLAY_PRESENTER_H

// Internal
#include "control_display_presenter.h"

// Qt
#include <QGeoCoordinate>

namespace presentation
{
    class VehicleDisplayPresenter: public ControlDisplayPresenter
    {
        Q_OBJECT

    public:
        explicit VehicleDisplayPresenter(QObject* parent = nullptr);
        ~VehicleDisplayPresenter() override;

    public slots:
        void setVehicle(int vehicleId) override;
        void updateMissionItems();

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateStatus(const domain::Telemetry::TelemetryMap& parameters);
        void updateAhrs(const domain::Telemetry::TelemetryMap& parameters);
        void updateCompass(const domain::Telemetry::TelemetryMap& parameters);
        void updateSatellite(const domain::Telemetry::TelemetryMap& parameters);
        void updatePowerSystem(const domain::Telemetry::TelemetryMap& parameters);
        void updatePitot(const domain::Telemetry::TelemetryMap& parameters);
        void updateBarometric(const domain::Telemetry::TelemetryMap& parameters);
        void updateRangefinder(const domain::Telemetry::TelemetryMap& parameters);
        void updatePosition(const domain::Telemetry::TelemetryMap& parameters);
        void updateHome(const domain::Telemetry::TelemetryMap& parameters);
        void updateNavigator(const domain::Telemetry::TelemetryMap& parameters);
        void updateWind(const domain::Telemetry::TelemetryMap& parameters);

    private:
        void updateHoming();

        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // VEHICLE_DISPLAY_PRESENTER_H
