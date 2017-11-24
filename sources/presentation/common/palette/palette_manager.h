#ifndef PALETTE_MANAGER_H
#define PALETTE_MANAGER_H

// Internal
#include "palette.h"

namespace presentation
{
    class PaletteManager: public QObject
    {
        Q_OBJECT

    public:
        enum Style
        {
            Outdoor,
            Indoor
        };

        explicit PaletteManager(QObject* parent = nullptr);

    public slots:
        void setPalette(const Palette& palette);
        void setPalette(Style paletteStyle);

        void loadSavedPalette();

    private:
        Q_ENUM(Style)
    };
}

#endif // PALETTE_MANAGER_H
