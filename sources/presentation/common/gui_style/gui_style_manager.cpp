#include "gui_style_manager.h"

// Qt
#include <QQmlContext>
#include <QVariant>
#include <QDebug>

// Industrial
#include "theme.h"
#include "theme_configurator.h"

// Internal
#include "settings_provider.h"
#include "presentation_context.h"

using namespace presentation;

GuiStyleManager::GuiStyleManager(QObject* parent):
    QObject(parent),
    m_configurator(new ThemeConfigurator(this))
{
    presentationContext->rootContext()->setContextProperty(
                "industrial", QVariant::fromValue(m_configurator->theme()));
}

GuiStyleManager::~GuiStyleManager()
{
}

void GuiStyleManager::setPaletteStyle(PaletteStyle paletteStyle)
{
    m_configurator->setPrimaryColor("#01c5a5");
    m_configurator->setOnPrimaryColor("#000000");

    switch (paletteStyle) {
    case Day:
        m_configurator->setBaseColor("#F5F5F5");
        m_configurator->setOnBaseColor("#F5F5F5");
        break;
    case Night:
        m_configurator->setBaseColor("#2d373e");
        m_configurator->setOnBaseColor("#ffffff");
        break;
    }
}

void GuiStyleManager::loadSettingsPalette()
{
    this->setPaletteStyle(PaletteStyle(settings::Provider::value(settings::gui::paletteStyle).toInt()));
}

void GuiStyleManager::setSizings(int baseSize)
{
    m_configurator->setBaseSize(baseSize);
}

void GuiStyleManager::loadSettingsSizings()
{
    this->setSizings(settings::Provider::value(settings::gui::uiSize).toInt());
}
