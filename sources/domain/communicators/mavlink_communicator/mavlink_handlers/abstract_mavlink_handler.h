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

        bool handleMessage(const mavlink_message_t& message);

    protected:
        virtual int messageId() const = 0;

    protected slots:
        virtual void processMessage(const mavlink_message_t& message) = 0;
    };
}

#endif // ABSTRACT_MAVLINK_HANDLER_H
