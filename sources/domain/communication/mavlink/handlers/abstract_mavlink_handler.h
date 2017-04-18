#ifndef ABSTRACT_MAVLINK_HANDLER_H
#define ABSTRACT_MAVLINK_HANDLER_H

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>

namespace data_source
{
    class MavLinkCommunicator;
}

namespace domain
{
    class AbstractMavLinkHandler: public QObject
    {
        Q_OBJECT

    public:
        AbstractMavLinkHandler(data_source::MavLinkCommunicator* communicator);
        ~AbstractMavLinkHandler() override;

    public slots:
        virtual void processMessage(const mavlink_message_t& message) = 0;

    protected:
        data_source::MavLinkCommunicator* const m_communicator;
    };
}

#endif // ABSTRACT_MAVLINK_HANDLER_H
