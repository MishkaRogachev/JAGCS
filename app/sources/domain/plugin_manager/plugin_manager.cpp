#include "plugin_manager.h"

// Qt
#include <QApplication>
#include <QMap>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

// Internal
#include "settings_provider.h"
#include "app_settings.h"

namespace
{
    const QString plugins = "plugins";
}

using namespace domain;

PluginManager* PluginManager::lastCreatedManager = nullptr;

class PluginManager::Impl
{
public:
    QMap<QString, QPluginLoader*> discoveredPlugins;
    QStringList loadedPlugins;
};

PluginManager::PluginManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    PluginManager::lastCreatedManager = this;
}

PluginManager::~PluginManager()
{
    this->saveConfiguration();
}

PluginManager* PluginManager::instance()
{
    return lastCreatedManager;
}

QStringList PluginManager::discoveredPlugins() const
{
    return d->discoveredPlugins.keys();
}

QStringList PluginManager::loadedPlugins() const
{
    return d->loadedPlugins;
}

QJsonObject PluginManager::pluginMetaData(const QString& plugin) const
{
    if (!d->discoveredPlugins.contains(plugin)) return QJsonObject();

    return d->discoveredPlugins[plugin]->metaData();
}

void PluginManager::discoverPlugins()
{
    QDir pluginsDir = qApp->applicationDirPath();
    if (!pluginsDir.cd(::plugins)) return;

    for (const QString& plugin: pluginsDir.entryList(QDir::Files))
    {
        if (d->discoveredPlugins.contains(plugin)) continue;

        QPluginLoader* loader = new QPluginLoader(pluginsDir.absoluteFilePath(plugin), this);
        if (loader->metaData().isEmpty())
        {
            delete loader;
            continue;
        }

        d->discoveredPlugins[plugin] = loader;
        emit pluginDiscovered(plugin);
    }
}

void PluginManager::loadPlugin(const QString& plugin)
{
    if (!d->discoveredPlugins.contains(plugin)) return;

    if (d->discoveredPlugins[plugin]->load())
    {
        d->loadedPlugins.append(plugin);
        emit pluginLoaded(plugin);
    }
}

void PluginManager::unloadPlugin(const QString& plugin)
{
    if (!d->discoveredPlugins.contains(plugin) || !d->loadedPlugins.contains(plugin)) return;

    if (d->discoveredPlugins[plugin]->unload())
    {
        d->loadedPlugins.removeOne(plugin);
        emit pluginUnloaded(plugin);
    }
}

void PluginManager::saveConfiguration()
{
    settings::Provider::setValue(settings::app::plugins, d->loadedPlugins);
}

void PluginManager::restoreConfiguration()
{
    QStringList loadingPlugins = settings::Provider::value(settings::app::plugins).toStringList();

    for (const QString& plugin: d->loadedPlugins)
    {
        if (!loadingPlugins.contains(plugin)) this->unloadPlugin(plugin);
    }

    for (const QString& plugin: loadingPlugins)
    {
        if (d->discoveredPlugins.contains(plugin)) this->loadPlugin(plugin);
    }
}
