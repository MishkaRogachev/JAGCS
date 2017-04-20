#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

#include "i_communicator_factory.h"

namespace domain
{
    class VehicleService;

    class MavLinkCommunicatorFactory: public ICommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory(VehicleService* vehicleServeice);

        data_source::AbstractCommunicator* create() override;

    private:
        VehicleService* m_vehicleServeice;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
