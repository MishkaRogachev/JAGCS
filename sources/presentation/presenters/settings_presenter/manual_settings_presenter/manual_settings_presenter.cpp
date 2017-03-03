#include "manual_settings_presenter.h"

// Internal
#include "settings_provider.h"
#include "settings.h"

using namespace presentation;

ManualSettingsPresenter::ManualSettingsPresenter(QObject* parent):
    BasePresenter(parent)
{}

void ManualSettingsPresenter::update()
{
    this->setViewProperty(PROPERTY(useJoystick), domain::SettingsProvider::value(
                              domain::manual_settings::useJoystick));
}

void ManualSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(setUseJoystick(bool)), this, SLOT(onSetUseJoystick(bool)));

    this->update();
}

void ManualSettingsPresenter::onSetUseJoystick(bool use)
{
    domain::SettingsProvider::setValue(domain::manual_settings::useJoystick, use);
}
