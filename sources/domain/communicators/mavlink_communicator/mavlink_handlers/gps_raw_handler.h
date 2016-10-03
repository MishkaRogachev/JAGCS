#ifndef GPS_RAW_HANDLER_H
#define GPS_RAW_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class GpsRawHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        GpsRawHandler(QObject* parent = nullptr);

    public slots:
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // GPS_RAW_HANDLER_H
