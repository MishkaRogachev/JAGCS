#ifndef ABSTRACT_PALETTE_FACTORY_H
#define ABSTRACT_PALETTE_FACTORY_H

#include "palette.h"

namespace presentation
{
    class AbstractPaletteFactory
    {
    public:
        AbstractPaletteFactory() {}
        virtual ~AbstractPaletteFactory() {}

        virtual Palette create();
    };
}

#endif // ABSTRACT_PALETTE_FACTORY_H
