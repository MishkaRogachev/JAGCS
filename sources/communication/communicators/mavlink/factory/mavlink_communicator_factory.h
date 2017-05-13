#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

#include "i_communicator_factory.h"

namespace domain
{
    class VehicleService;
    class MissionService;
}

namespace comm
{
    class MavLinkCommunicatorFactory: public ICommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory(domain::VehicleService* vehicleServeice,
                                   domain::MissionService* missionService,
                                   quint8 systemId, quint8 componentId);

        AbstractCommunicator* create() override;

    private:
        domain::VehicleService* m_vehicleService;
        domain::MissionService* m_missionService;
        quint8 m_systemId;
        quint8 m_componentId;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
