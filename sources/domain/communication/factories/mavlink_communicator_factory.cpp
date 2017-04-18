#include "mavlink_communicator_factory.h"

// Internal
#include "settings_provider.h"
#include "mavlink_communicator.h"

#include "ping_handler.h"

using namespace data_source;
using namespace domain;

MavLinkCommunicatorFactory::MavLinkCommunicatorFactory():
    ICommunicatorFactory()
{}

AbstractCommunicator* MavLinkCommunicatorFactory::create()
{
    auto communicator = new MavLinkCommunicator(
         SettingsProvider::value(settings::communication::systemId).toInt(),
         SettingsProvider::value(settings::communication::componentId).toInt());

    new PingHandler(communicator);

    return communicator;
}
