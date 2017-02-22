#ifndef RC_CHANNELS_HANDLER_H
#define RC_CHANNELS_HANDLER_H

#include "abstract_mavlink_handler.h"

// Qt
#include <QMap>

namespace domain
{
    class VehicleService;

    class RcChannelsHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        RcChannelsHandler(VehicleService* vehicleService,
                          MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendChannelsOverride(const QMap<int, int>& channels);

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // RC_CHANNELS_HANDLER_H
