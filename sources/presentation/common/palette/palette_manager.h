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
        explicit PaletteManager(QObject* parent = nullptr);

    public slots:
        void setPalette(const Palette& palette);

    };
}

#endif // PALETTE_MANAGER_H
