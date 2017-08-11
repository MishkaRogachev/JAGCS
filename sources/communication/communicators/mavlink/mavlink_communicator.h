#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "abstract_communicator.h"

// MAVLink
#include <mavlink_types.h>

namespace comm
{
    class MavLinkCommunicator: public AbstractCommunicator
    {
        Q_OBJECT

    public:
         MavLinkCommunicator(uint8_t systemId, uint8_t componentId,
                             QObject* parent = nullptr);
        ~MavLinkCommunicator() override;

        bool isAddLinkEnabled() override;

        uint8_t systemId() const;
        uint8_t componentId() const;

        uint8_t linkChannel(AbstractLink* link) const;

        AbstractLink* lastReceivedLink() const;
        AbstractLink* mavSystemLink(uint8_t systemId);

    public slots:
        void addLink(AbstractLink* link) override;
        void removeLink(AbstractLink* link) override;

        void setSystemId(uint8_t systemId);
        void setComponentId(uint8_t componentId);

        void sendMessage(mavlink_message_t& message, AbstractLink* link);

    signals:
        void messageReceived(const mavlink_message_t& message);
        void systemIdChanged(uint8_t systemId);
        void componentIdChanged(uint8_t componentId);

    protected slots:
        void onDataReceived(const QByteArray& data) override;

    protected:
        virtual void finalizeMessage(mavlink_message_t& message);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
