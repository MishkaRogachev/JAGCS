#include "night_palette_factory.h"

using namespace presentation;

Palette NightPaletteFactory::create()
{
    Palette palette = AbstractPaletteFactory::create();

    palette.setSkyColor("#00d4ff");
    palette.setGroundColor("#7b4837");

    palette.setSunkenColor("#102027");
    palette.setBackgroundColor("#2d373e");
    palette.setRaisedColor("#37474f");
    palette.setControlColor("#4f5b62");
    palette.setButtonColor("#607C88");

    palette.setTextColor("#ffffff");
    palette.setSecondaryTextColor("#e0e0e0");
    palette.setSelectedTextColor("#000000");

    palette.setHighlightColor("#02eec8");
    palette.setSelectionColor("#00c98f");

    return palette;
}
