#include "gui_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "units.h"

#include "presentation_context.h"
#include "translation_manager.h"
#include "gui_style_manager.h"

namespace
{
    QList<utils::Units::SpeedUnits> availableSpeedUnits =
    { utils::Units::Mps, utils::Units::Kph, utils::Units::Knots, utils::Units::Mph };

    QList<utils::Units::DistanceUnits> availableAltitudeUnits =
    { utils::Units::Meters, utils::Units::Feets };
}

using namespace presentation;

class GuiSettingsPresenter::Impl
{
public:
    GuiStyleManager guiStyleManager;
};

GuiSettingsPresenter::GuiSettingsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

GuiSettingsPresenter::~GuiSettingsPresenter()
{}

int GuiSettingsPresenter::speedUnitFromIndex(int index)
{
    return ::availableSpeedUnits.at(index);
}

int GuiSettingsPresenter::altitudeUnitFromIndex(int index)
{
    return ::availableAltitudeUnits.at(index);
}

void GuiSettingsPresenter::updateView()
{
#ifdef Q_OS_ANDROID
    this->setViewProperty(PROPERTY(fullscreenVisible), false);
#else
    this->setViewProperty(PROPERTY(fullscreenVisible), true);
#endif

    this->setViewProperty(PROPERTY(fullscreen), settings::Provider::value(settings::gui::fullscreen));

    const QStringList& locales = translationManager->avalibleLocales();
    int index = locales.indexOf(translationManager->currentLocale());
    this->setViewProperty(PROPERTY(locales), locales);
    this->setViewProperty(PROPERTY(localeIndex), index);

    QStringList availableSpeedUnits;
    for (utils::Units::SpeedUnits unit: ::availableSpeedUnits)
    {
        availableSpeedUnits.append(utils::Units::trSpeedUnits(unit));
    }
    this->setViewProperty(PROPERTY(availableSpeedUnits), QVariant::fromValue(availableSpeedUnits));
    int speedUnitsIndex = ::availableSpeedUnits.indexOf(
                              settings::Provider::value(
                                  settings::gui::fdSpeedUnits).value<
                              utils::Units::SpeedUnits>());
    this->setViewProperty(PROPERTY(speedUnits), speedUnitsIndex);

    QStringList availableAltitudeUnits;
    for (utils::Units::DistanceUnits unit: ::availableAltitudeUnits)
    {
        availableAltitudeUnits.append(utils::Units::trDistanceUnits(unit));
    }
    this->setViewProperty(PROPERTY(availableAltitudeUnits),
                          QVariant::fromValue(availableAltitudeUnits));
    int altitudeUnitsIndex = ::availableAltitudeUnits.indexOf(
                                 settings::Provider::value(
                                     settings::gui::fdAltitudeUnits).value<
                                 utils::Units::DistanceUnits>());
    this->setViewProperty(PROPERTY(altitudeUnits), altitudeUnitsIndex);

    this->setViewProperty(PROPERTY(uiSize),
                          settings::Provider::value(settings::gui::uiSize));
    this->setViewProperty(PROPERTY(paletteStyle),
                          settings::Provider::value(settings::gui::paletteStyle));
    this->setViewProperty(PROPERTY(rollInverted),
                          settings::Provider::value(settings::gui::fdRollInverted));
    this->setViewProperty(PROPERTY(speedStep),
                          settings::Provider::value(settings::gui::fdSpeedStep));
    this->setViewProperty(PROPERTY(altitudeStep),
                          settings::Provider::value(settings::gui::fdAltitudeStep));
    this->setViewProperty(PROPERTY(relativeAltitude),
                          settings::Provider::value(settings::gui::fdRelativeAltitude));
    this->setViewProperty(PROPERTY(coordinatesDms),
                          settings::Provider::value(settings::gui::coordinatesDms));

    this->setViewProperty(PROPERTY(changed), false);
}

void GuiSettingsPresenter::save()
{
    settings::Provider::setValue(settings::gui::fullscreen,
                                 this->viewProperty(PROPERTY(fullscreen)).toBool());
    settings::Provider::setValue(settings::gui::uiSize,
                                 this->viewProperty(PROPERTY(uiSize)).toInt());
    settings::Provider::setValue(settings::gui::paletteStyle,
                                 this->viewProperty(PROPERTY(paletteStyle)));
    settings::Provider::setValue(settings::gui::fdRollInverted,
                                 this->viewProperty(PROPERTY(rollInverted)));
    settings::Provider::setValue(settings::gui::fdSpeedStep,
                                 this->viewProperty(PROPERTY(speedStep)));
    settings::Provider::setValue(settings::gui::fdSpeedUnits,
                                 this->speedUnitFromIndex(
                                     this->viewProperty(PROPERTY(speedUnits)).toInt()));
    settings::Provider::setValue(settings::gui::fdAltitudeStep,
                                 this->viewProperty(PROPERTY(altitudeStep)));
    settings::Provider::setValue(settings::gui::fdAltitudeUnits,
                                 this->altitudeUnitFromIndex(
                                     this->viewProperty(PROPERTY(altitudeUnits)).toInt()));
    settings::Provider::setValue(settings::gui::fdRelativeAltitude,
                                 this->viewProperty(PROPERTY(relativeAltitude)));
    settings::Provider::setValue(settings::gui::coordinatesDms,
                                 this->viewProperty(PROPERTY(coordinatesDms)));

    this->setLocale(this->viewProperty(PROPERTY(localeIndex)).toInt(), true);

    d->guiStyleManager.loadSettingsSizings();
    d->guiStyleManager.loadSettingsPalette();

    presentationContext->saveWindowedGeometry();
    presentationContext->updateGeometry();

    this->setViewProperty(PROPERTY(changed), false);
}

void GuiSettingsPresenter::setFullscreen(bool fullscreen)
{
    presentationContext->updateGeometry(fullscreen);
}

void GuiSettingsPresenter::setLocale(int localeIndex, bool save)
{
    const QStringList& locales = translationManager->avalibleLocales();
    QString locale = locales.value(localeIndex);

    translationManager->setLocale(locale);
    if (save) settings::Provider::setValue(settings::gui::locale, locale);
}

void GuiSettingsPresenter::setUiSize(int size)
{
    d->guiStyleManager.setSizings(size);
}

void GuiSettingsPresenter::setPalleteStyle(int paletteStyle)
{
    d->guiStyleManager.setPaletteStyle(static_cast<GuiStyleManager::PaletteStyle>(paletteStyle));
}
