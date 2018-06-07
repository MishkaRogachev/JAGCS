#include "day_palette_factory.h"

using namespace presentation;

Palette DayPaletteFactory::create()
{
    Palette palette = AbstractPaletteFactory::create();

    palette.setSkyColor("#61ffff");
    palette.setGroundColor("#4bda63");

    palette.setSunkenColor("#babdbe");
    palette.setBackgroundColor("#eceff1");
    palette.setRaisedColor("#f0f4f0");
    palette.setControlColor("#b8b8b8");
    palette.setButtonColor("#cfd8dc");

    palette.setTextColor("#202020");
    palette.setSecondaryTextColor("#b8b8b8");

    palette.setHighlightColor("#14cba8");
    palette.setSelectionColor("#9fffe0");
    palette.setSelectedTextColor("#000000");
    
    return palette;
}
