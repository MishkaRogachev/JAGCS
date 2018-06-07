#include "night_palette_factory.h"

using namespace presentation;

Palette NightPaletteFactory::create()
{
    Palette palette = AbstractPaletteFactory::create();

    palette.setSkyColor("#00d4ff");
    palette.setGroundColor("#7b4837");

    palette.setSunkenColor("#262e31");
    palette.setBackgroundColor("#30393d");
    palette.setRaisedColor("#384348");
    palette.setControlColor("#465763");
    palette.setButtonColor("#54646b");

    palette.setTextColor("#f6f5f0");
    palette.setSecondaryTextColor("#aeb0b3");

    return palette;
}
