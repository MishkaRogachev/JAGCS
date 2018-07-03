#ifndef DAY_PALETTE_FACTORY_H
#define DAY_PALETTE_FACTORY_H

#include "abstract_palette_factory.h"

namespace presentation
{
    class DayPaletteFactory: public AbstractPaletteFactory
    {
    public:
        Palette create() override;
    };
}

#endif // DAY_PALETTE_FACTORY_H
