#ifndef AUTOPILOT_VERSION_HANDLER_H
#define AUTOPILOT_VERSION_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace comm
{
    class AutopilotVersionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        AutopilotVersionHandler(MavLinkCommunicator* communicator);
        ~AutopilotVersionHandler() override;

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void requestVersion(quint8 mavId);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // AUTOPILOT_VERSION_HANDLER_H
