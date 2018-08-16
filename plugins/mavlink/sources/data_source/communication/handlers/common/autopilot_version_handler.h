#ifndef AUTOPILOT_VERSION_HANDLER_H
#define AUTOPILOT_VERSION_HANDLER_H

// Qt
#include <QObject>

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class TelemetryService;
}

namespace data_source
{
    class AutopilotVersionHandler: public QObject, public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit AutopilotVersionHandler(MavLinkCommunicator* communicator);
        ~AutopilotVersionHandler() override;

        void processMessage(const mavlink_message_t& message) override;

    public slots:
        void requestVersion(quint8 mavId);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // AUTOPILOT_VERSION_HANDLER_H
