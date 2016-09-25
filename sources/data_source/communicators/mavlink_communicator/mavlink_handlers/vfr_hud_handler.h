#ifndef VFR_HUD_HANDLER_H
#define VFR_HUD_HANDLER_H

#include "abstract_mavlink_handler.h"

namespace data_source
{
    class VfrHudHandler: public AbstractMavLinkHandler
    {
    public:
        VfrHudHandler();

    protected:
        int messageId() const override;
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // VFR_HUD_HANDLER_H
