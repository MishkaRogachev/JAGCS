#ifndef MAVLINK_ABSTRACT_LINK_H
#define MAVLINK_ABSTRACT_LINK_H

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>

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
            void statusUpdated(mavlink_status_t status);

        protected:
            virtual void sendData(const QByteArray& data) = 0;
            void resolveData(const QByteArray& data);
        };
    }
}

#endif // MAVLINK_ABSTRACT_LINK_H
