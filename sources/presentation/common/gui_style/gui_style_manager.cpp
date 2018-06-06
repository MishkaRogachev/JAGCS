#include "gui_style_manager.h"

// Qt
#include <QQmlContext>
#include <QVariant>

// Internal
#include "settings_provider.h"

#include "presentation_context.h"

using namespace presentation;

GuiStyleManager::GuiStyleManager(QObject* parent): QObject(parent)
{}

void GuiStyleManager::setPalette(const Palette& palette)
{
    presentationContext->rootContext()->setContextProperty("customPalette", QVariant::fromValue(palette));
}

void GuiStyleManager::setPalette(GuiStyleManager::PaletteStyle paletteStyle)
{
    // TODO: store palette in files
    Palette palette;

    palette.setTrackColor("#64adf6");
    palette.setMissionColor("#1ce9a5");
    palette.setActiveMissionColor("#fd00fd");

    palette.setSkyColor(paletteStyle ? "#61ffff" : "#00d4ff");
    palette.setGroundColor(paletteStyle ? "#4bda63" : "#7b4837");

    palette.setSunkenColor(paletteStyle ? "#c3c6ce" : "#262e31");
    palette.setBackgroundColor(paletteStyle ? "#ced1da" : "#30393d");
    palette.setRaisedColor(paletteStyle ? "#e1e5ee" : "#384348");
    palette.setControlColor(paletteStyle ? "#91a1ad" : "#465763");
    palette.setButtonColor(paletteStyle ? "#f6f5f0" : "#54646b");

    palette.setTextColor(paletteStyle ? "#30393d" : "#f6f5f0");
    palette.setSecondaryTextColor(paletteStyle ? "#435056" : "#aeb0b3");
    palette.setSelectedTextColor("#070707");

    palette.setHighlightColor("#1effb4");
    palette.setSelectedTextColor("#070707");

    palette.setHighlightColor("#1effb4");
    palette.setSelectionColor("#1ce9a5");
    palette.setLinkColor("#64adf6");

    palette.setDangerColor("#e53535");
    palette.setCautionColor("#ff9800");
    palette.setPositiveColor("#86c34a");

    this->setPalette(palette);
}

void GuiStyleManager::loadSettingsPalette()
{
    this->setPalette(PaletteStyle(settings::Provider::value(settings::gui::paletteStyle).toInt()));
}

void GuiStyleManager::setSizings(const Sizings& sizings)
{
    presentationContext->rootContext()->setContextProperty("sizings", QVariant::fromValue(sizings));
}

void GuiStyleManager::setSizings(int controlBaseSize)
{
    Sizings sizings;

    sizings.setControlBaseSize(controlBaseSize);
    sizings.setInputControlHeight(controlBaseSize * 1.25);
    sizings.setFontSize(controlBaseSize / 2);
    sizings.setSecondaryFontSize(controlBaseSize / 2.5);
    sizings.setSpacing(controlBaseSize / 4);
    sizings.setMargins(controlBaseSize / 4);
    sizings.setPadding(controlBaseSize / 6);
    sizings.setShadowSize(3);

    this->setSizings(sizings);
}

void GuiStyleManager::loadSettingsSizings()
{
    this->setSizings(settings::Provider::value(settings::gui::uiSize).toInt());
}
