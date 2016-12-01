#ifndef I_MAVLINK_COMMUNICATOR_FACTORY_H
#define I_MAVLINK_COMMUNICATOR_FACTORY_H

namespace domain
{
    class VehicleService;
    class MissionService;

    class MavLinkCommunicator;

    class IMavLinkCommunicatorFactory
    {
    public:
        IMavLinkCommunicatorFactory(VehicleService* vehicleService,
                                    MissionService* missionService):
            m_vehicleService(vehicleService),
            m_missionService(missionService)
        {}

        virtual ~IMavLinkCommunicatorFactory() {}

        virtual MavLinkCommunicator* create() = 0;

    protected:
        VehicleService* const m_vehicleService;
        MissionService* const m_missionService;
    };
}

#endif // I_MAVLINK_COMMUNICATOR_FACTORY_H
