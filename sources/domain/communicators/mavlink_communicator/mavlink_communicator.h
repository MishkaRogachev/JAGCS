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

        QList<AbstractLink*> links() const override;

    public slots:
        void addLink(AbstractLink* link) override;
        void removeLink(AbstractLink* link) override;

        //void receiveData(const QByteArray& data, AbstractLink* link) override;

    private slots:
        void onDataReceived(const QByteArray& data);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
