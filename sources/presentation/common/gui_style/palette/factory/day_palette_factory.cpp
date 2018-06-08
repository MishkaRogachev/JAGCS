#include "day_palette_factory.h"

using namespace presentation;

Palette DayPaletteFactory::create()
{
    Palette palette = AbstractPaletteFactory::create();

    palette.setSkyColor("#00d4ff");
    palette.setGroundColor("#4bda63");

    palette.setSunkenColor("#babdbe");
    palette.setBackgroundColor("#e8ecf0");
    palette.setRaisedColor("#ffffff");
    palette.setControlColor("#90a4ae");
    palette.setButtonColor("#cfd8dc");

    palette.setTextColor("#202020");
    palette.setSecondaryTextColor("#546e7a");

    palette.setHighlightColor("#14cba8");
    palette.setSelectionColor("#9fffe0");
    palette.setSelectedTextColor("#ffffff");
    
    return palette;
}
