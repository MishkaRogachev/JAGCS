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
                          settings::Provider::value(settings::manual::joystick::enabled));
    this->setViewProperty(PROPERTY(device),
                          settings::Provider::value(settings::manual::joystick::device));
    this->setViewProperty(PROPERTY(pitchAxis),
                          settings::Provider::value(settings::manual::joystick::pitch::axis));
    this->setViewProperty(PROPERTY(pitchFactor),
                          settings::Provider::value(settings::manual::joystick::pitch::factor));
    this->setViewProperty(PROPERTY(rollAxis),
                          settings::Provider::value(settings::manual::joystick::roll::axis));
    this->setViewProperty(PROPERTY(rollFactor),
                          settings::Provider::value(settings::manual::joystick::roll::factor));
    this->setViewProperty(PROPERTY(throttleAxis),
                          settings::Provider::value(settings::manual::joystick::throttle::axis));
    this->setViewProperty(PROPERTY(throttleFactor),
                          settings::Provider::value(settings::manual::joystick::throttle::factor));
    this->setViewProperty(PROPERTY(yawAxis),
                          settings::Provider::value(settings::manual::joystick::yaw::axis));
    this->setViewProperty(PROPERTY(yawFactor),
                          settings::Provider::value(settings::manual::joystick::yaw::factor));

    this->setViewProperty(PROPERTY(changed), false);
}

void JoystickSettingsPresenter::save()
{
    settings::Provider::setValue(settings::manual::joystick::enabled,
                                 this->viewProperty(PROPERTY(joystickEnabled)).toBool());
    settings::Provider::setValue(settings::manual::joystick::device,
                                 this->viewProperty(PROPERTY(device)).toInt());
    settings::Provider::setValue(settings::manual::joystick::pitch::axis,
                                 this->viewProperty(PROPERTY(pitchAxis)).toInt());
    settings::Provider::setValue(settings::manual::joystick::pitch::factor,
                                 this->viewProperty(PROPERTY(pitchFactor)).toInt());
    settings::Provider::setValue(settings::manual::joystick::roll::axis,
                                 this->viewProperty(PROPERTY(rollAxis)).toInt());
    settings::Provider::setValue(settings::manual::joystick::roll::factor,
                                 this->viewProperty(PROPERTY(rollFactor)).toInt());
    settings::Provider::setValue(settings::manual::joystick::throttle::axis,
                                 this->viewProperty(PROPERTY(throttleAxis)).toInt());
    settings::Provider::setValue(settings::manual::joystick::throttle::factor,
                                 this->viewProperty(PROPERTY(throttleFactor)).toInt());
    settings::Provider::setValue(settings::manual::joystick::yaw::axis,
                                 this->viewProperty(PROPERTY(yawAxis)).toInt());
    settings::Provider::setValue(settings::manual::joystick::yaw::factor,
                                 this->viewProperty(PROPERTY(yawFactor)).toInt());

    this->setViewProperty(PROPERTY(changed), false);
}

