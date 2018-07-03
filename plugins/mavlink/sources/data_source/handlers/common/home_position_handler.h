#ifndef HOME_POSITION_HANDLER_H
#define HOME_POSITION_HANDLER_H

// Qt
#include <QObject>

// Internal
#include "abstract_mavlink_handler.h"

namespace comm
{
    class HomePositionHandler: public QObject, public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        explicit HomePositionHandler(MavLinkCommunicator* communicator);
        ~HomePositionHandler();

        void processMessage(const mavlink_message_t& message) override;

    public slots:
        void sendHomePositionRequest(quint8 mavId);

    protected:
        void timerEvent(QTimerEvent* event) override;

    private slots:
        void addVehicleTimer(int vehicleId);
        void removeVehicleTimer(int vehicleId);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // HOME_POSITION_HANDLER_H
