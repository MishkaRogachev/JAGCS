#ifndef CONTROL_DISPLAY_PRESENTER_H
#define CONTROL_DISPLAY_PRESENTER_H

// Internal
#include "abstract_telemetry_presenter.h"

namespace presentation
{
    class ControlDisplayPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit ControlDisplayPresenter(QObject* parent = nullptr);
        ~ControlDisplayPresenter() override;

    public slots:
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

#endif // CONTROL_DISPLAY_PRESENTER_H
