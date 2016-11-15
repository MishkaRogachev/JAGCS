#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

// Qt
#include <QMap>
#include <QBasicTimer>

// Internal
#include "abstract_mavlink_handler.h"

namespace domain
{
    class VehicleService;
    class Position;

    class HomePositionHandler: public AbstractMavLinkHandler
    {
    public:
        HomePositionHandler(VehicleService* vehicleService,
                            MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePositionRequest(uint8_t id);
        void sendHomePositionSetting(uint8_t id, const Position& position);

    protected:
        void timerEvent(QTimerEvent* event);

    private slots:
        void onVehicleAdded(uint8_t id);
        void onVehicleRemoved(uint8_t id);

    private:
        VehicleService* const m_vehicleService;
        QMap<uint8_t, QBasicTimer> m_reqestTimers;
    };
}

#endif // HOMEPOSITIONHANDLER_H
