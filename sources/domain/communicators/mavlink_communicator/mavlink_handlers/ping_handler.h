#ifndef PING_HANDLER_H
#define PING_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace domain
{
    class PingHandler: public AbstractMavLinkHandler
    {
    public:
        PingHandler(int systemId, int componentId);

        int systemId() const;
        void setSystemId(int systemId);

        int componentId() const;
        void setComponentId(int componentId);

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;

    private:
        int m_systemId;
        int m_componentId;
    };
}

#endif // PING_HANDLER_H
