#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_command_handler.h"
#include "abstract_mavlink_handler.h"

#include "vehicle_types.h"

namespace comm
{
    class CommandHandler: // Rename to MavLinkCommandHandler
            public domain::AbstractCommandHandler,
            public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit CommandHandler(MavLinkCommunicator* communicator);
        ~CommandHandler() override;

        void processMessage(const mavlink_message_t& message) override;

    public slots:
        void processCommandAck(const mavlink_message_t& message);
        void processHeartbeat(const mavlink_message_t& message);

    protected:
        void sendCommand(int vehicleId, const dto::CommandPtr& command, int attempt = 0) override;

    private slots:
        // TODO: move command to processors/handlers/senders
        void sendCommandLong(quint8 mavId, quint16 commandId, const QVariantList& args, int attempt);
        void sendSetMode(quint8 mavId, domain::vehicle::Mode mode);
        void sendCurrentItem(quint8 mavId, quint16 seq);
        void sendNavTo(quint8 mavId, double latitude, double longitude, float altitude);
        void sendSetAltitude(quint8 mavId, float altitude);
        void sendSetLoiterRadius(quint8 mavId, float radius);
        void sendManualControl(quint8 mavId, float pitch, float roll, float yaw, float thrust);

        void onVehicleRemoved(const dto::VehiclePtr& vehicle);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_HANDLER_H
