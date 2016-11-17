#ifndef I_MAVLINK_COMMUNICATOR_FACTORY_H
#define I_MAVLINK_COMMUNICATOR_FACTORY_H

namespace domain
{
    class VehicleService;
    class MavLinkCommunicator;

    class IMavLinkCommunicatorFactory
    {
    public:
        IMavLinkCommunicatorFactory(VehicleService* vehicleService):
            m_vehicleService(vehicleService)
        {}

        virtual ~IMavLinkCommunicatorFactory() {}

        virtual MavLinkCommunicator* create() = 0;

    protected:
        VehicleService* m_vehicleService;
    };
}

#endif // I_MAVLINK_COMMUNICATOR_FACTORY_H
