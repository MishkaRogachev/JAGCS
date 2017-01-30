#ifndef SETTINGS_H
#define SETTINGS_H

namespace domain
{
    namespace gui_settings
    {
        const char* const locale = "Gui/locale";
        const char* const uiSize = "Gui/uiSize";
        const char* const paletteStyle = "Gui/paletteStyle";
        const char* const fdRollInverted = "Gui/fdRollInverted";
    }

    namespace map_settings
    {
        const char* const zoomLevel = "Map/zoomLevel";
        const char* const centerLatitude = "Map/centerLatitude";
        const char* const centerLongitude = "Map/centerLongitude";
    }

    namespace video_settings
    {
        const char* const device = "Video/device";
    }

    namespace proxy_settings
    {
        const char* const type = "NetworkProxy/type";
        const char* const hostName = "NetworkProxy/hostName";
        const char* const port = "NetworkProxy/port";
        const char* const user = "NetworkProxy/user";
        const char* const password = "NetworkProxy/password";
    }

    namespace connection_settings
    {
        const char* const systemId = "Connection/systemId";
        const char* const componentId = "Connection/componentId";
        const char* const serialDevice = "Connection/serialDevice";
        const char* const baudRate = "Connection/baudRate";
        const char* const port = "Connection/port";
    }

    namespace mission_settings
    {
        const char* const defaultAcceptanceRadius = "Mission/defaultAcceptanceRadius";
        const char* const defaultTakeoffPitch = "Mission/defaultTakeoffPitch";
    }
}

#endif // SETTINGS_H
