#include "plugins_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "plugin_manager.h"

using namespace presentation;

PluginsPresenter::PluginsPresenter(QObject* parent):
    BasePresenter(parent)
{
    connect(pluginManager, &domain::PluginManager::pluginDiscovered,
            this, &PluginsPresenter::updatePlugins);
}

void PluginsPresenter::updatePlugins()
{
    QVariantList discoveredPlugins;

    for (const QString& plugin: pluginManager->discoveredPlugins())
    {
        discoveredPlugins.append(pluginManager->pluginMetaData(plugin));
    }

    this->setViewProperty(PROPERTY(discoveredPlugins), discoveredPlugins);
}

void PluginsPresenter::discoverPlugins()
{
    pluginManager->discoverPlugins();
}
