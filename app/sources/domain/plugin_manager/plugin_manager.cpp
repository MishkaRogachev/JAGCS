#include "plugin_manager.h"

// Qt
#include <QApplication>
#include <QDir>
#include <QPluginLoader>
#include <QDebug>

namespace
{
    const QString plugins = "plugins";
}

using namespace domain;

class PluginManager::Impl
{
public:
    QList<QJsonObject> discoveredPlugins;
};

PluginManager::PluginManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

PluginManager::~PluginManager()
{}

QList<QJsonObject> PluginManager::discoveredPlugins() const
{
    return d->discoveredPlugins;
}

void PluginManager::discoverPlugins()
{
    QDir pluginsDir = qApp->applicationDirPath();
    if (!pluginsDir.cd(::plugins)) return;

    d->discoveredPlugins.clear();
    for (const QString& fileName: pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

        d->discoveredPlugins.append(loader.metaData());
        qDebug() << loader.fileName() << loader.metaData();
    }
}
