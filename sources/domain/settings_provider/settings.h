#ifndef SETTINGS_H
#define SETTINGS_H

namespace domain
{
    namespace gui_settings
    {
        const char* const group = "Gui";
        const char* const uiSize = "uiSize";
        const char* const paletteStyle = "paletteStyle";
    }

    namespace proxy_settings
    {
        const char* const group = "NetworkProxy";
        const char* const type = "type";
        const char* const hostName = "hostName";
        const char* const port = "port";
        const char* const user = "user";
        const char* const password = "password";
    }

    namespace connection_settings
    {
        const char* const group = "Connection";
        const char* const systemId = "systemId";
        const char* const componentId = "componentId";
        const char* const serialDevice = "serialDevice";
        const char* const baudRate = "baudRate";
        const char* const port = "port";
    }

    namespace map_settings
    {
        const char* const group = "Map";
        const char* const zoomLevel = "zoomLevel";
        const char* const centerLatitude = "centerLatitude";
        const char* const centerLongitude = "centerLongitude";
    }

    namespace video_settings
    {
        const char* const group = "Video";
        const char* const device = "device";
    }
}

#endif // SETTINGS_H
