#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

#include "i_mavlink_communicator_factory.h"

namespace domain
{
    class MavLinkCommunicatorFactory: public IMavLinkCommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory(VehicleService* vehicleService,
                                   MissionService* missionService);

        MavLinkCommunicator* create() override;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
