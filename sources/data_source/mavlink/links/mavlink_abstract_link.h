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

            virtual bool isUp() const = 0;

        public slots:
            virtual void up() = 0;
            virtual void down() = 0;

            void sendMessage(const mavlink_message_t& message);

        signals:
            void messageReceived(mavlink_message_t message);

        protected:
            virtual void sendData(const QByteArray& data) = 0;
            void resolveData(const QByteArray& data);
        };
    }
}

#endif // MAVLINK_ABSTRACT_LINK_H
