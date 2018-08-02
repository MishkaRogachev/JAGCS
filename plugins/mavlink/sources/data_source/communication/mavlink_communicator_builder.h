#ifndef MAVLINK_COMMUNICATOR_BUILDER_H
#define MAVLINK_COMMUNICATOR_BUILDER_H

// Qt
#include <QtGlobal>

namespace data_source
{
    class MavLinkCommunicator;

    class MavLinkCommunicatorBuilder
    {
    public:
        MavLinkCommunicatorBuilder();
        ~MavLinkCommunicatorBuilder();

        void initCommunicator();
        MavLinkCommunicator* getCommunicator();

        void buildIdentification(quint8 systemId, quint8 componentId);
        void buildHandlers();

    private:
        MavLinkCommunicator* m_communicator;
    };
}

#endif // MAVLINK_COMMUNICATOR_BUILDER_H
