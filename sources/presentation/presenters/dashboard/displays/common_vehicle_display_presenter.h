#ifndef COMMON_VEHICLE_DISPLAY_PRESENTER_H
#define COMMON_VEHICLE_DISPLAY_PRESENTER_H

// Internal
#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class CommonVehicleDisplayPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit CommonVehicleDisplayPresenter(QObject* parent = nullptr);
        ~CommonVehicleDisplayPresenter() override;

    public slots:
        virtual void setVehicle(int vehicleId);

        void executeCommand(int commandType, const QVariant& args);
        void rejectCommand(int commandType);

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateStatus(const domain::Telemetry::TelemetryMap& parameters);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMON_VEHICLE_DISPLAY_PRESENTER_H
