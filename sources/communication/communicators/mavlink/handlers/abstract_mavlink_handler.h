#ifndef ABSTRACT_MAVLINK_HANDLER_H
#define ABSTRACT_MAVLINK_HANDLER_H

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>

namespace comm
{
    class MavLinkCommunicator;

    class AbstractMavLinkHandler: public QObject
    {
        Q_OBJECT

    public:
        AbstractMavLinkHandler(MavLinkCommunicator* communicator);
        ~AbstractMavLinkHandler() override;

    public slots:
        virtual void processMessage(const mavlink_message_t& message) = 0;

    protected:
        MavLinkCommunicator* const m_communicator;
    };
}

#endif // ABSTRACT_MAVLINK_HANDLER_H
