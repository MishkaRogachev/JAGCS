#ifndef NIGHT_PALETTE_FACTORY_H
#define NIGHT_PALETTE_FACTORY_H

#include "abstract_palette_factory.h"

namespace presentation
{
    class NightPaletteFactory: public AbstractPaletteFactory
    {
    public:
        Palette create() override;
    };
}

#endif // NIGHT_PALETTE_FACTORY_H
