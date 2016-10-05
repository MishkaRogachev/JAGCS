#ifndef ABSTRACT_MAVLINK_HANDLER_H
#define ABSTRACT_MAVLINK_HANDLER_H

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>

namespace domain
{
    class AbstractMavLinkHandler: public QObject
    {
        Q_OBJECT

    public:
        AbstractMavLinkHandler(QObject* parent);
        ~AbstractMavLinkHandler() override;

    public slots:
        virtual void processMessage(const mavlink_message_t& message) = 0;

    signals:
        void sendMessage(mavlink_message_t& message);
    };
}

#endif // ABSTRACT_MAVLINK_HANDLER_H
