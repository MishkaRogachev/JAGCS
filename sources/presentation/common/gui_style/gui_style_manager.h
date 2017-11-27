#ifndef GUI_STYLE_MANAGER_H
#define GUI_STYLE_MANAGER_H

// Internal
#include "palette.h"
#include "sizings.h"

namespace presentation
{
    class GuiStyleManager: public QObject
    {
        Q_OBJECT

    public:
        enum PaletteStyle
        {
            Outdoor,
            Indoor
        };

        explicit GuiStyleManager(QObject* parent = nullptr);

    public slots:
        void setPalette(const Palette& palette);
        void setPalette(PaletteStyle paletteStyle);
        void loadSavedPalette();

        void setSizings(const Sizings& sizings);
        void setSizings(int controlBaseSize);
        void loadSavedSizings();

    private:
        Q_ENUM(PaletteStyle)
    };
}

#endif // GUI_STYLE_MANAGER_H
