#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

// Internal
#include "i_communicator_factory.h"
#include "mavlink_communicator.h"

namespace comm
{
    class MavLinkCommunicatorFactory: public ICommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory(quint8 systemId, quint8 componentId, bool retranslationEnabled);

        MavLinkCommunicator* create() override;

    private:
        quint8 m_systemId;
        quint8 m_componentId;
        bool m_retranslationEnabled;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
