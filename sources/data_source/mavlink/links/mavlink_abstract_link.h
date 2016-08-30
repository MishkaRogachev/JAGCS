#ifndef MAVLINK_ABSTRACT_LINK_H
#define MAVLINK_ABSTRACT_LINK_H

// Qt
#include <QObject>

// Internal
#include "mavlink_traits.h"

namespace data_source
{
    namespace mavlink
    {
        class AbstractLink: public QObject
        {
            Q_OBJECT

        public:
            explicit AbstractLink(QObject* parent);

        public slots:
            void sendMessage(const mavlink_message_t& message);

        signals:
            void messageReceived(mavlink_message_t message);

        protected:
            virtual void sendData(const QByteArray& data) = 0;
        };
    }
}

#endif // MAVLINK_ABSTRACT_LINK_H
