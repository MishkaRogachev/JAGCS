#include "gui_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "translation_manager.h"

using namespace presentation;

GuiSettingsPresenter::GuiSettingsPresenter(QObject* parent):
    BasePresenter(parent)
{}

void GuiSettingsPresenter::updateView()
{
    this->setViewProperty(PROPERTY(fullscreen), settings::Provider::value(settings::gui::fullscreen));

    const QStringList& locales = domain::TranslationManager::avalibleLocales();
    int index = locales.indexOf(domain::TranslationManager::currentLocale());
    this->setViewProperty(PROPERTY(localeIndex), index);

    this->setViewProperty(PROPERTY(uiSize), settings::Provider::value(settings::gui::uiSize));
    this->setViewProperty(PROPERTY(paletteStyle), settings::Provider::value(settings::gui::paletteStyle));
    this->setViewProperty(PROPERTY(fdRollInverted), settings::Provider::value(settings::gui::fdRollInverted));

}

void GuiSettingsPresenter::connectView(QObject* view)
{
    this->setViewProperty(PROPERTY(locales), QVariant::fromValue(
                              domain::TranslationManager::avalibleLocales()));
    this->updateView();

    connect(view, SIGNAL(updateSettings()), this, SLOT(onUpdateSettings()));
}

void GuiSettingsPresenter::onUpdateSettings()
{
    settings::Provider::setValue(settings::gui::fullscreen, this->viewProperty(PROPERTY(fullscreen)).toBool());

    const QStringList& locales = domain::TranslationManager::avalibleLocales();
    QString locale = locales.value(this->viewProperty(PROPERTY(localeIndex)).toInt());
    domain::TranslationManager::setCurrentLocale(locale);

    settings::Provider::setValue(settings::gui::uiSize, this->viewProperty(PROPERTY(uiSize)).toInt());
    settings::Provider::setValue(settings::gui::paletteStyle, this->viewProperty(PROPERTY(paletteStyle)));
    settings::Provider::setValue(settings::gui::fdRollInverted, this->viewProperty(PROPERTY(fdRollInverted)));
}
