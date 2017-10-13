#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "modes.h"

namespace domain
{
    class Command;
}

namespace comm
{
    class CommandHandler: public AbstractMavLinkHandler // TODO: separate command handlers
    {
        Q_OBJECT

    public:
        explicit CommandHandler(MavLinkCommunicator* communicator);
        ~CommandHandler() override;

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void processCommandAck(const mavlink_message_t& message);
       void processHeartbeat(const mavlink_message_t& message);

    private slots:
       void onSendCommand(const domain::Command& command, int attempt = 0);

       void sendCommandLong(quint8 mavId, quint16 commandId, const QVariantList& args, int attempt);
       void sendSetMode(quint8 mavId, domain::Mode mode);
       void sendCurrentItem(quint8 mavId, quint16 seq);
       void sentNavTo(quint8 mavId, double latitude, double longitude, float altitude);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // COMMAND_HANDLER_H
