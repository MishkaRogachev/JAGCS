#include "plugin_manager.h"

// Qt
#include <QApplication>
#include <QMap>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

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
};

PluginManager::PluginManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    PluginManager::lastCreatedManager = this;
}

PluginManager::~PluginManager()
{}

PluginManager*PluginManager::instance()
{
    return lastCreatedManager;
}

QStringList PluginManager::discoveredPlugins() const
{
    return d->discoveredPlugins.keys();
}

void PluginManager::discoverPlugins()
{
    QDir pluginsDir = qApp->applicationDirPath();
    if (!pluginsDir.cd(::plugins)) return;

    QMap<QString, QPluginLoader*> newPlugins;
    for (const QString& fileName: pluginsDir.entryList(QDir::Files))
    {
        if (d->discoveredPlugins.contains(fileName))
        {
            newPlugins.insert(fileName, d->discoveredPlugins.take(fileName));
            continue;
        }

        QPluginLoader* loader = new QPluginLoader(pluginsDir.absoluteFilePath(fileName), this);
        if (loader->metaData().isEmpty())
        {
            delete loader;
            continue;
        }

        newPlugins.insert(fileName, loader);
    }

    while (!d->discoveredPlugins.isEmpty())
    {
        delete d->discoveredPlugins.take(d->discoveredPlugins.firstKey());
    }

    d->discoveredPlugins = newPlugins;
}
