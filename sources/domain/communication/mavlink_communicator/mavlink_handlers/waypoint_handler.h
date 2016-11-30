#ifndef WAYPOINT_HANDLER_H
#define WAYPOINT_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;

    class WaypointHandler: public AbstractMavLinkHandler
    {
    public:
        WaypointHandler(VehicleService* vehicleService,
                        MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void requestList(uint8_t id);
        void requestWaypoint(uint8_t id, uint8_t waypoint);

    private:
        VehicleService* m_vehicleService;
    };
}

#endif // WAYPOINT_HANDLER_H
