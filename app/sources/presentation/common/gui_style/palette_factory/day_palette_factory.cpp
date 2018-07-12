#include "day_palette_factory.h"

using namespace presentation;

Palette DayPaletteFactory::create()
{
    Palette palette = AbstractPaletteFactory::create();

    palette.setSkyColor("#00d4ff");
    palette.setGroundColor("#4bda63");

    palette.setSunkenColor("#B0BEC5");
    palette.setBackgroundColor("#F5F5F5");
    palette.setRaisedColor("#ECEFF1");
    palette.setControlColor("#CFD8DC");
    palette.setButtonColor("#CFD8DC");

    palette.setTextColor("#202020");
    palette.setSecondaryTextColor("#546e7a");
    palette.setSelectedTextColor("#ffffff");

    palette.setHighlightColor("#00c98f");
    palette.setSelectionColor("#02eec8");
    
    return palette;
}
