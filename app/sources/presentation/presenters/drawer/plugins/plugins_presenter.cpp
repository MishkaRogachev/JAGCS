#include "plugins_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "plugin_manager.h"

using namespace presentation;

PluginsPresenter::PluginsPresenter(QObject* parent):
    BasePresenter(parent)
{}

void PluginsPresenter::updatePlugins()
{
    this->setViewProperty(PROPERTY(discoveredPlugins), pluginManager->discoveredPlugins());
}
