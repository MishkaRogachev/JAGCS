#ifndef CONTROL_DISPLAY_PRESENTER_H
#define CONTROL_DISPLAY_PRESENTER_H

// Internal
#include "abstract_telemetry_presenter.h"

namespace domain
{
    class CommandService;
}

namespace presentation
{
    class ControlDisplayPresenter: public AbstractTelemetryPresenter
    {
        Q_OBJECT

    public:
        explicit ControlDisplayPresenter(QObject* parent = nullptr);

    public slots:
        void executeCommand(int commandType, const QVariant& args);
        void rejectCommand(int commandType);

    protected:
        void connectNode(domain::Telemetry* node) override;

    private slots:
        void updateStatus(const domain::Telemetry::TelemetryMap& parameters);

    private:
        domain::CommandService* const m_service;
    };
}

#endif // CONTROL_DISPLAY_PRESENTER_H
