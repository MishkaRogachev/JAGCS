#ifndef SETTINGS_H
#define SETTINGS_H

namespace settings
{
    namespace data_base
    {
        const char* const name = "Data_base/name";
    }

    namespace gui
    {
        const char* const fullscreen = "Gui/fullscreen";
        const char* const locale = "Gui/locale";
        const char* const uiSize = "Gui/uiSize";
        const char* const paletteStyle = "Gui/paletteStyle";
        const char* const fdRollInverted = "Gui/fdRollInverted";
    }

    namespace map
    {
        const char* const zoomLevel = "Map/zoomLevel";
        const char* const centerLatitude = "Map/centerLatitude";
        const char* const centerLongitude = "Map/centerLongitude";
    }

    namespace video
    {
        const char* const device = "Video/device";
    }

    namespace proxy
    {
        const char* const type = "NetworkProxy/type";
        const char* const hostName = "NetworkProxy/hostName";
        const char* const port = "NetworkProxy/port";
        const char* const user = "NetworkProxy/user";
        const char* const password = "NetworkProxy/password";
    }

    namespace communication
    {
        const char* const systemId = "Communication/systemId";
        const char* const componentId = "Communication/componentId";
        const char* const autoAdd = "Communication/autoAdd";
        const char* const baudRate = "Communication/baudRate";
        const char* const port = "Communication/port";
        const char* const statisticsCount = "Communication/statisticsCount";
    }

    namespace telemetry
    {
        const char* const timeout = "Telemetry/timeout";
    }

    namespace mission
    {
        const char* const defaultAcceptanceRadius = "Mission/defaultAcceptanceRadius";
        const char* const defaultTakeoffPitch = "Mission/defaultTakeoffPitch";
    }
}

#endif // SETTINGS_H
