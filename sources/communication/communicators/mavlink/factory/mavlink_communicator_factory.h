#ifndef MAVLINK_COMMUNICATOR_FACTORY_H
#define MAVLINK_COMMUNICATOR_FACTORY_H

#include "i_communicator_factory.h"

namespace db
{
    class DbFacade;
}

namespace domain
{
    class TelemetryService;
    class CommandService;
}

namespace comm
{
    class MavLinkCommunicatorFactory: public ICommunicatorFactory
    {
    public:
        MavLinkCommunicatorFactory(db::DbFacade* dbFacade,
                                   domain::TelemetryService* telemetryService,
                                   domain::CommandService* commandService,
                                   quint8 systemId, quint8 componentId);

        AbstractCommunicator* create() override;

    private:
        db::DbFacade* m_dbFacade;
        domain::TelemetryService* m_telemetryService;
        domain::CommandService* m_commandService;
        quint8 m_systemId;
        quint8 m_componentId;
    };
}

#endif // MAVLINK_COMMUNICATOR_FACTORY_H
