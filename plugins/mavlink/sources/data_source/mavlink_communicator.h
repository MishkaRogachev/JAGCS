#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "abstract_communicator.h"

// MAVLink
#include <mavlink_types.h>

namespace comm
{
    class AbstractMavLinkHandler;

    class MavLinkCommunicator: public AbstractCommunicator
    {
        Q_OBJECT

    public:
         MavLinkCommunicator(quint8 systemId, quint8 componentId, QObject* parent = nullptr);
        ~MavLinkCommunicator() override;

        bool isAddLinkEnabled() override;

        quint8 systemId() const;
        quint8 componentId() const;

        quint8 linkChannel(AbstractLink* link) const;

        AbstractLink* lastReceivedLink() const;
        AbstractLink* mavSystemLink(quint8 systemId);

    public slots:
        void addLink(AbstractLink* link) override;
        void removeLink(AbstractLink* link) override;

        void switchLinkProtocol(AbstractLink* link, Protocol protocol);

        void setSystemId(quint8 systemId);
        void setComponentId(quint8 componentId);

        void addHandler(AbstractMavLinkHandler* handler);

        void sendMessage(mavlink_message_t& message, AbstractLink* link);

    signals:
        void systemIdChanged(quint8 systemId);
        void componentIdChanged(quint8 componentId);

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
