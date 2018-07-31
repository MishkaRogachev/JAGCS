#include "plugins_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "plugin_manager.h"
#include "plugins_list_model.h"

using namespace presentation;

class PluginsPresenter::Impl
{
public:
    PluginsListModel model;
};

PluginsPresenter::PluginsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    for (const QString& plugin: pluginManager->discoveredPlugins())
    {
        this->onPluginDiscovered(plugin);
    }

    connect(pluginManager, &domain::PluginManager::pluginDiscovered,
            this, &PluginsPresenter::onPluginDiscovered);
}

PluginsPresenter::~PluginsPresenter()
{}

void PluginsPresenter::discoverPlugins()
{
    pluginManager->discoverPlugins();
}

void PluginsPresenter::connectView(QObject* view)
{
     view->setProperty(PROPERTY(discoveredPlugins), QVariant::fromValue(&d->model));
}

void PluginsPresenter::onPluginDiscovered(const QString& plugin)
{
    QJsonObject meta = pluginManager->pluginMetaData(plugin);
    meta.insert(::enabled, pluginManager->loadedPlugins().contains(plugin));

    d->model.addPluginData(plugin, pluginManager->pluginMetaData(plugin));
}

