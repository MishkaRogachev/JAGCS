#ifndef GUI_STYLE_MANAGER_H
#define GUI_STYLE_MANAGER_H

// Internal
#include "sizings.h"

namespace presentation
{
    class GuiStyleManager: public QObject
    {
        Q_OBJECT

    public:
        enum PaletteStyle
        {
            Night,
            Day
        };

        explicit GuiStyleManager(QObject* parent = nullptr);

    public slots:
        void setPaletteStyle(PaletteStyle paletteStyle);
        void loadSettingsPalette();

        void setSizings(const Sizings& sizings);
        void setSizings(int controlBaseSize);
        void loadSettingsSizings();

    private:
        Q_ENUM(PaletteStyle)
    };
}

#endif // GUI_STYLE_MANAGER_H
