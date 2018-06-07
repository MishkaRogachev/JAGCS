#include "abstract_palette_factory.h"

using namespace presentation;

Palette AbstractPaletteFactory::create()
{
    Palette palette;

    palette.setTrackColor("#64adf6");
    palette.setMissionColor("#1ce9a5");
    palette.setActiveMissionColor("#fd00fd");

    palette.setLinkColor("#64adf6");

    palette.setDangerColor("#e53535");
    palette.setCautionColor("#ff9800");
    palette.setPositiveColor("#86c34a");

    return palette;
}
