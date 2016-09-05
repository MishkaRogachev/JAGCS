#ifndef SETTINGS_H
#define SETTINGS_H

namespace domain
{
    namespace gui_settings
    {
        const char* const group = "Gui";
        const char* const toolbarWidth = "toolbarWidth";
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
        const char* const serialDevice = "serialDevice";
        const char* const baudRate = "baudRate";
        const char* const hostPort = "hostPort";
        const char* const address = "address";
        const char* const port = "port";
    }

    namespace video_settings
    {
        const char* const group = "Video";
        const char* const device = "device";
    }
}

#endif // SETTINGS_H
