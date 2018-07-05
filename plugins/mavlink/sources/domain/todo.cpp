    comm::MavLinkCommunicatorFactory commFactory(
                settings::Provider::value(settings::communication::systemId).toInt(),
                settings::Provider::value(settings::communication::componentId).toInt()); 
