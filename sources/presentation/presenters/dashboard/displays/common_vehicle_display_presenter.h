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
        void setVehicle(int vehicleId);

        void updateVehicle();
        void updateMission();

        void executeCommand(int commandType, const QVariant& args);
        void rejectCommand(int commandType);

    protected:
        void connectView(QObject* view) override;

        void setVehicleProperty(const char* name, const QVariant& value);
        void setVehicleProperty(const QString& group, const char* name, const QVariant& value);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMON_VEHICLE_DISPLAY_PRESENTER_H
