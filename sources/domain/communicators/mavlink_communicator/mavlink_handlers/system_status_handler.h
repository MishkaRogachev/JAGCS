#ifndef SYSTEM_STATUS_HANDLER_H
#define SYSTEM_STATUS_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class SystemStatusHandler: public AbstractMavLinkHandler
    {
        Q_OBJECT

    public:
        SystemStatusHandler(QObject* parent = nullptr);

    protected:
        int messageId() const override;

    protected slots:
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // SYSTEM_STATUS_HANDLER_H
