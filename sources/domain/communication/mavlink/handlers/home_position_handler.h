#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

// Qt
#include <QMap>
#include <QBasicTimer>

// Internal
#include "abstract_mavlink_handler.h"
#include "db_traits.h"

namespace domain
{
    class VehicleService;
    class Position;

    class HomePositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        HomePositionHandler(VehicleService* vehicleService,
                            data_source::MavLinkCommunicator* communicator);

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePositionRequest(uint8_t id);
        void sendHomePositionSetting(const Position& position);

    protected:
        void timerEvent(QTimerEvent* event);

    private slots:
        void onVehicleAdded(const data_source::VehicleDescriptionPtr& description);
        void onVehicleRemoved(const data_source::VehicleDescriptionPtr& description);

    private:
        VehicleService* const m_vehicleService;
        QMap<data_source::VehicleDescriptionPtr, QBasicTimer> m_reqestTimers;
    };
}

#endif // HOMEPOSITIONHANDLER_H
