#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

#include "i_communicator_factory.h"

namespace data_source
{
    class MavLinkCommunicatorFactory: public ICommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory(quint8 systemId, quint8 componentId);

        AbstractCommunicator* create() override;

    private:
        quint8 m_systemId;
        quint8 m_componentId;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
