#include "joystick_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

using namespace presentation;

JoystickSettingsPresenter::JoystickSettingsPresenter(QObject* parent):
    BasePresenter(parent)
{}

void JoystickSettingsPresenter::updateView()
{
    this->setViewProperty(PROPERTY(joystickEnabled),
                          settings::Provider::value(settings::joystick::enabled));
    this->setViewProperty(PROPERTY(device),
                          settings::Provider::value(settings::joystick::device));
    this->setViewProperty(PROPERTY(pitchAxis),
                          settings::Provider::value(settings::joystick::pitchAxis));
    this->setViewProperty(PROPERTY(rollAxis),
                          settings::Provider::value(settings::joystick::rollAxis));
    this->setViewProperty(PROPERTY(yawAxis),
                          settings::Provider::value(settings::joystick::yawAxis));
    this->setViewProperty(PROPERTY(throttleAxis),
                          settings::Provider::value(settings::joystick::throttleAxis));

    this->setViewProperty(PROPERTY(changed), false);
}

void JoystickSettingsPresenter::save()
{
    settings::Provider::setValue(settings::joystick::enabled,
                                 this->viewProperty(PROPERTY(joystickEnabled)).toBool());
    settings::Provider::setValue(settings::joystick::device,
                                 this->viewProperty(PROPERTY(device)).toInt());
    settings::Provider::setValue(settings::joystick::pitchAxis,
                                 this->viewProperty(PROPERTY(pitchAxis)).toInt());
    settings::Provider::setValue(settings::joystick::rollAxis,
                                 this->viewProperty(PROPERTY(rollAxis)).toInt());
    settings::Provider::setValue(settings::joystick::yawAxis,
                                 this->viewProperty(PROPERTY(yawAxis)).toInt());
    settings::Provider::setValue(settings::joystick::throttleAxis,
                                 this->viewProperty(PROPERTY(throttleAxis)).toInt());

    this->setViewProperty(PROPERTY(changed), false);
}

