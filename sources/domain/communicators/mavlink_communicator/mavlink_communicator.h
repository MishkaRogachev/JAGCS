#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "abstract_communicator.h"

namespace domain
{
    class MavLinkCommunicator: public AbstractCommunicator
    {
        Q_OBJECT

    public:
        explicit MavLinkCommunicator(VehicleService* vehicleService,
                                     QObject* parent = nullptr);
        ~MavLinkCommunicator() override;

    public slots:
        void addLink(AbstractLink* link) override;
        void removeLink(AbstractLink* link) override;

    protected slots:
        void onDataReceived(const QByteArray& data) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
