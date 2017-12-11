#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

// Qt
#include <QObject>

// Internal
#include "dao_traits.h"

#include "abstract_mavlink_handler.h"
#include "modes.h"

namespace comm
{
    class CommandHandler: public QObject, public AbstractMavLinkHandler // TODO: separate command handlers
    {
        Q_OBJECT

    public:
        explicit CommandHandler(MavLinkCommunicator* communicator);
        ~CommandHandler() override;

        void processMessage(const mavlink_message_t& message) override;

    public slots:
       void processCommandAck(const mavlink_message_t& message);
       void processHeartbeat(const mavlink_message_t& message);

    private slots:
       void onSendCommand(const dao::CommandPtr& command, int attempt = 0);

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
