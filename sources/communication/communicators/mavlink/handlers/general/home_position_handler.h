#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

// Internal
#include "abstract_mavlink_handler.h"

namespace comm
{
    class HomePositionHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        HomePositionHandler(MavLinkCommunicator* communicator);
        ~HomePositionHandler();

    public slots:
        void processMessage(const mavlink_message_t& message) override;

        void sendHomePositionRequest(quint8 mavId);

    protected:
        void timerEvent(QTimerEvent* event);

    private slots:
        void addVehicleTimer(int vehicleId);
        void removeVehicleTimer(int vehicleId);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // HOME_POSITION_HANDLER_H
