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
    domain::SettingsProvider::beginGroup(domain::gui_settings::group);

    this->setViewProperty(PROPERTY(uiSize), domain::SettingsProvider::value(
                              domain::gui_settings::uiSize));
    this->setViewProperty(PROPERTY(paletteStyle), domain::SettingsProvider::value(
                              domain::gui_settings::paletteStyle));

    domain::SettingsProvider::endGroup();
}

void GuiSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(setUiSize(int)), this, SLOT(onSetUiSize(int)));
    connect(view, SIGNAL(setPaletteStyle(int)), this, SLOT(onSetPaletteStyle(int)));

    this->updateView();
}

void GuiSettingsPresenter::onSetUiSize(int size)
{
    domain::SettingsProvider::beginGroup(domain::gui_settings::group);

    domain::SettingsProvider::setValue(domain::gui_settings::uiSize, size);

    domain::SettingsProvider::endGroup();
}

void GuiSettingsPresenter::onSetPaletteStyle(int paletteStyle)
{
    domain::SettingsProvider::beginGroup(domain::gui_settings::group);

    domain::SettingsProvider::setValue(domain::gui_settings::paletteStyle, paletteStyle);

    domain::SettingsProvider::endGroup();
}
