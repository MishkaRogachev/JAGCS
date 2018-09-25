#include "gui_style_manager.h"

// Qt
#include <QQmlContext>
#include <QVariant>

// Internal
#include "settings_provider.h"

#include "presentation_context.h"
#include "day_palette_factory.h"
#include "night_palette_factory.h"

using namespace presentation;

GuiStyleManager::GuiStyleManager(QObject* parent): QObject(parent)
{}

void GuiStyleManager::setPaletteStyle(PaletteStyle paletteStyle)
{
    QScopedPointer<AbstractPaletteFactory> factory;

    switch (paletteStyle) {
    case Day:
        factory.reset(new DayPaletteFactory());
        break;
    case Night:
        factory.reset(new NightPaletteFactory());
        break;
    default:
        break;
    }

    if (!factory) return;

    presentationContext->rootContext()->setContextProperty(
                "customPalette", QVariant::fromValue(factory->create()));
}

void GuiStyleManager::loadSettingsPalette()
{
    this->setPaletteStyle(PaletteStyle(settings::Provider::value(settings::gui::paletteStyle).toInt()));
}

void GuiStyleManager::setSizings(const ControlSize& controlSize)
{
    presentationContext->rootContext()->setContextProperty("controlSize",
                                                           QVariant::fromValue(controlSize));
}

void GuiStyleManager::setSizings(int baseSize)
{
    ControlSize controlSize;

    controlSize.setBaseSize(baseSize);
    controlSize.setInputControlHeight(baseSize * 1.25);
    controlSize.setFontSize(baseSize / 2);
    controlSize.setSecondaryFontSize(controlSize.fontSize() * 0.75);
    controlSize.setSpacing(baseSize / 4);
    controlSize.setMargins(baseSize / 4);
    controlSize.setPadding(baseSize / 6);
    controlSize.setShadowSize(3);

    this->setSizings(controlSize);
}

void GuiStyleManager::loadSettingsSizings()
{
    this->setSizings(settings::Provider::value(settings::gui::uiSize).toInt());
}
