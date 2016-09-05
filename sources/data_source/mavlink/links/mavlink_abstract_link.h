#ifndef MAVLINK_ABSTRACT_LINK_H
#define MAVLINK_ABSTRACT_LINK_H

// Internal
#include "i_link.h"

// MAVLink
#include <mavlink_types.h>

namespace data_source
{
    namespace mavlink
    {
        class AbstractLink: public ILink
        {
            Q_OBJECT

        public:
            explicit AbstractLink(QObject* parent);

        public slots:
            void sendMessage(const mavlink_message_t& message);

        signals:
            void messageReceived(mavlink_message_t message);
            void statusUpdated(mavlink_status_t status);

        protected:
            virtual void sendData(const QByteArray& data) = 0;
            void resolveData(const QByteArray& data);
        };
    }
}

#endif // MAVLINK_ABSTRACT_LINK_H
