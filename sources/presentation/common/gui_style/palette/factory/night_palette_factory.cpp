#include "night_palette_factory.h"

using namespace presentation;

Palette NightPaletteFactory::create()
{
    Palette palette = AbstractPaletteFactory::create();

    palette.setSkyColor("#00d4ff");
    palette.setGroundColor("#7b4837");

    palette.setSunkenColor("#203038");
    palette.setBackgroundColor("#304448");
    palette.setRaisedColor("#37474f");
    palette.setControlColor("#4f5b62");
    palette.setButtonColor("#607C88");

    palette.setTextColor("#ffffff");
    palette.setSecondaryTextColor("#e0e0e0");

    palette.setHighlightColor("#68f0a8");
    palette.setSelectionColor("#28bc78");
    palette.setSelectedTextColor("#000000");

    return palette;
}
