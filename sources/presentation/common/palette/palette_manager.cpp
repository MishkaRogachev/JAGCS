#include "palette_manager.h"

// Qt
#include <QQmlContext>
#include <QVariant>

// Internal
#include "settings_provider.h"

#include "presentation_context.h"

using namespace presentation;

PaletteManager::PaletteManager(QObject* parent): QObject(parent)
{}

void PaletteManager::setPalette(const Palette& palette)
{
    PresentationContext::rootContext()->setContextProperty("palette", QVariant::fromValue(palette));
}

void PaletteManager::reloadPalette()
{
    Palette palette;

    int uiSize = settings::Provider::value(settings::gui::uiSize).toInt();
    int paletteStyle = settings::Provider::value(settings::gui::paletteStyle).toInt();

    palette.setControlBaseSize(uiSize);
    palette.setFontPixelSize(uiSize / 2);
    palette.setSpacing(uiSize / 4);
    palette.setMargins(uiSize / 4);
    palette.setPadding(uiSize / 5);

    palette.setTrackColor("#ff173c");
    palette.setMissionColor("#1ce9a5");
    palette.setActiveMissionColor("#fd00fd");

    palette.setSkyColor(paletteStyle ? "#61ffff" : "#00d4ff");
    palette.setGroundColor(paletteStyle ? "#4bda63" : "#7b4837");

    palette.setBackgroundColor(paletteStyle ? "#ced1da" : "#30393d");
    palette.setSunkenColor(paletteStyle ? "#c3c6ce" : "#262e31");
    palette.setRaisedColor(paletteStyle ? "#e1e5ee" : "#384348");
    palette.setButtonColor(paletteStyle ? "#f6f5f0" : "#54646b");

    palette.setTextColor(paletteStyle ? "#30393d" : "#f6f5f0");
    palette.setSelectedTextColor("#070707");

    palette.setHighlightColor("#1effb4");
    palette.setSelectedTextColor("#070707");

    palette.setHighlightColor("#1effb4");
    palette.setSelectionColor("#1ce9a5");

    palette.setDangerColor("#e53535");
    palette.setCautionColor("#ff9800");
    palette.setPositiveColor("#86c34a");

    this->setPalette(palette);
}
