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
    class AbstractVehicle;
    class Position;

    class HomePositionHandler: public AbstractMavLinkHandler
    {
    public:
        HomePositionHandler(VehicleService* vehicleService,
                            MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePositionRequest(uint8_t id);
        void sendHomePositionSetting(const Position& position);

    protected:
        void timerEvent(QTimerEvent* event);

    private slots:
        void onVehicleAdded(AbstractVehicle* vehicle);
        void onVehicleRemoved(AbstractVehicle* vehicle);

    private:
        VehicleService* const m_vehicleService;
        QMap<uint8_t, QBasicTimer> m_reqestTimers;
    };
}

#endif // HOMEPOSITIONHANDLER_H
