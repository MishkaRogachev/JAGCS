#include "map_settings_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "settings_provider.h"

using namespace presentation;

MapSettingsPresenter::MapSettingsPresenter(QObject* parent):
    BasePresenter(parent)
{}

void MapSettingsPresenter::updateView()
{
    this->setViewProperty(PROPERTY(activeMapType),
                          settings::Provider::value(settings::map::activeMapType));
    this->setViewProperty(PROPERTY(tileHost),
                          settings::Provider::value(settings::map::tileHost));
    this->setViewProperty(PROPERTY(cacheSize),
                          settings::Provider::value(settings::map::cacheSize));
    this->setViewProperty(PROPERTY(highdpiTiles),
                          settings::Provider::value(settings::map::highdpiTiles));
    this->setViewProperty(PROPERTY(trackLength),
                          settings::Provider::value(settings::map::trackLength));

    this->setViewProperty(PROPERTY(changed), false);
}

void MapSettingsPresenter::save()
{
    settings::Provider::setValue(settings::map::activeMapType,
                                 this->viewProperty(PROPERTY(activeMapType)));
    settings::Provider::setValue(settings::map::tileHost,
                                 this->viewProperty(PROPERTY(tileHost)));
    settings::Provider::setValue(settings::map::cacheSize,
                                 this->viewProperty(PROPERTY(cacheSize)));
    settings::Provider::setValue(settings::map::highdpiTiles,
                                 this->viewProperty(PROPERTY(highdpiTiles)));
    settings::Provider::setValue(settings::map::trackLength,
                                 this->viewProperty(PROPERTY(trackLength)).toInt());

    this->setViewProperty(PROPERTY(changed), false);
}

void MapSettingsPresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));

    this->updateView();
}


