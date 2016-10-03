#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "abstract_communicator.h"

// MAVLink
#include <mavlink_types.h>

namespace domain
{
    class MavLinkCommunicator: public AbstractCommunicator
    {
        Q_OBJECT

    public:
        explicit MavLinkCommunicator(VehicleService* vehicleService,
                                     QObject* parent = nullptr);
        ~MavLinkCommunicator() override;

        uint8_t systemId() const;
        uint8_t componentId() const;

    public slots:
        void addLink(AbstractLink* link) override;
        void removeLink(AbstractLink* link) override;

        void setSystemId(uint8_t systemId);
        void setComponentId(uint8_t componentId);

        void sendMessage(const mavlink_message_t& message);

    signals:
        void systemIdChanged(uint8_t systemId);
        void componentIdChanged(uint8_t componentId);

    protected slots:
        void onDataReceived(const QByteArray& data) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
