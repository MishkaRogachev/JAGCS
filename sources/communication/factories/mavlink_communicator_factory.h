#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

#include "i_communicator_factory.h"

namespace domain
{
    class DomainEntry;
}

namespace comm
{
    class MavLinkCommunicatorFactory: public ICommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory(domain::DomainEntry* entry, quint8 systemId,
                                   quint8 componentId);

        AbstractCommunicator* create() override;

    private:
        domain::DomainEntry* m_entry;
        quint8 m_systemId;
        quint8 m_componentId;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
