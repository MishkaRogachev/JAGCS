#include "gui_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "settings.h"

using namespace presentation;

GuiSettingsPresenter::GuiSettingsPresenter(QObject* parent):
    BasePresenter(parent)
{}

void GuiSettingsPresenter::updateView()
{
    this->setViewProperty(PROPERTY(uiSize), domain::SettingsProvider::value(
                              domain::gui_settings::uiSize));
    this->setViewProperty(PROPERTY(paletteStyle), domain::SettingsProvider::value(
                              domain::gui_settings::paletteStyle));
}

void GuiSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(updateSettings()), this, SLOT(onUpdateSettings()));

    this->updateView();
}

void GuiSettingsPresenter::onUpdateSettings()
{
    domain::SettingsProvider::setValue(domain::gui_settings::uiSize,
                                       this->viewProperty(PROPERTY(uiSize)).toInt());
    domain::SettingsProvider::setValue(domain::gui_settings::paletteStyle,
                                       this->viewProperty(PROPERTY(paletteStyle)));
}
