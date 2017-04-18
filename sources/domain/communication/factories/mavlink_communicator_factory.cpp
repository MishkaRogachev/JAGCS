#include "mavlink_communicator_factory.h"

// Internal
#include "mavlink_communicator.h"

#include "settings_provider.h"

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

    return communicator;
}
