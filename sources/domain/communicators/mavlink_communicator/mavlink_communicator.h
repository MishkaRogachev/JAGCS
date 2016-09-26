#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include "abstract_communicator.h"

namespace data_source
{
    class MavLinkCommunicator: public AbstractCommunicator
    {
        Q_OBJECT

    public:
        explicit MavLinkCommunicator(QObject* parent = nullptr);
        ~MavLinkCommunicator() override;

        void receiveData(const QByteArray& data, AbstractLink* link) override;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
