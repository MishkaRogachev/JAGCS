#ifndef MAVLINK_PLUIGN_H
#define MAVLINK_PLUIGN_H

// Internal
#include "i_communication_plugin.h"
#include "i_db_plugin.h"

namespace domain
{
    class MavlinkPlugin: public QObject,
            public ICommunicationPlugin,
            public IDbPlugin
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "domain.MavlinkPlugin" FILE "meta.json")
        Q_INTERFACES(domain::ICommunicationPlugin)
        Q_INTERFACES(domain::IDbPlugin)

    public:
        explicit MavlinkPlugin(QObject* parent = nullptr);

        data_source::AbstractCommunicator* createCommunicator() override;

        QList<data_source::DbMigrationPtr> migrations() const override;
    };
}

#endif // MAVLINK_PLUIGN_H
