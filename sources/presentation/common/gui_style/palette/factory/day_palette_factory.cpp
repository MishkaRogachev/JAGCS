#include "day_palette_factory.h"

using namespace presentation;

Palette DayPaletteFactory::create()
{
    Palette palette = AbstractPaletteFactory::create();

    palette.setSkyColor("#61ffff");
    palette.setGroundColor("#4bda63");

    palette.setSunkenColor("#c3c6ce");
    palette.setBackgroundColor("#ced1da");
    palette.setRaisedColor("#e1e5ee");
    palette.setControlColor("#91a1ad");
    palette.setButtonColor("#f6f5f0");

    palette.setTextColor("#30393d");
    palette.setSecondaryTextColor("#435056");
    
    return palette;
}
