#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

#include "i_communicator_factory.h"

namespace domain
{
    class MavLinkCommunicatorFactory: public ICommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory();

        data_source::AbstractCommunicator* create() override;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
