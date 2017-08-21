#ifndef MISSION_HANDLER_H
#define MISSION_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"
#include "dao_traits.h"

namespace domain
{
    class TelemetryService;
    class VehicleService;
    class MissionService;
}

namespace comm
{
    class MissionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        enum class Stage
        {
            Idle,
            WaitingCount,
            WaitingItem
        };

        MissionHandler(MavLinkCommunicator* communicator);
        ~MissionHandler() override;

    public slots:
       void processMessage(const mavlink_message_t& message) override;

       void download(const dao::MissionAssignmentPtr& assignment);
       void upload(const dao::MissionAssignmentPtr& assignment);
       void selectCurrent(int vehicleId, uint16_t seq);

       void requestMissionCount(uint8_t mavId);
       void requestMissionItem(uint8_t mavId, uint16_t seq);

       void sendMissionItem(uint8_t mavId, uint16_t seq);
       void sendMissionAck(uint8_t mavId);
       void sendCurrentItem(uint8_t mavId, uint16_t seq);

    protected:
        void processMissionCount(const mavlink_message_t& message);
        void processMissionItem(const mavlink_message_t& message);
        void processMissionRequest(const mavlink_message_t& message);
        void processMissionAck(const mavlink_message_t& message);
        void processMissionCurrent(const mavlink_message_t& message);
        void processMissionReached(const mavlink_message_t& message);

        void startStage(Stage stage, quint8 mavId);
        void timerEvent(QTimerEvent* event);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // MISSION_HANDLER_H
