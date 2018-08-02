#ifndef MAVLINK_PLUIGN_H
#define MAVLINK_PLUIGN_H

#include "i_communication_plugin.h"

namespace domain
{
    class MavlinkPlugin: public QObject, public ICommunicationPlugin
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "domain.ICommunicationPlugin" FILE "meta.json")
        Q_INTERFACES(domain::ICommunicationPlugin)

    public:
        explicit MavlinkPlugin(QObject* parent = nullptr);

        data_source::AbstractCommunicator* createCommunicator() override;
    };
}

#endif // MAVLINK_PLUIGN_H
