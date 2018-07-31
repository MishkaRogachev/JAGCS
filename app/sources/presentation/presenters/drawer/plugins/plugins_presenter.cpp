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
        this->setPlugin(plugin);
    }

    connect(pluginManager, &domain::PluginManager::pluginDiscovered,
            this, &PluginsPresenter::setPlugin);
    connect(pluginManager, &domain::PluginManager::pluginLoaded,
            this, &PluginsPresenter::setPlugin);
    connect(pluginManager, &domain::PluginManager::pluginUnloaded,
            this, &PluginsPresenter::setPlugin);
    connect(&d->model, &PluginsListModel::requestEnablePlugin,
            this, &PluginsPresenter::onRequestEnablePlugin);
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

void PluginsPresenter::setPlugin(const QString& plugin)
{
    QJsonObject meta = pluginManager->pluginMetaData(plugin);
    meta.insert(::enabled, pluginManager->loadedPlugins().contains(plugin));

    d->model.setPlugin(plugin, meta);
}

void PluginsPresenter::onRequestEnablePlugin(const QString& plugin, bool enable)
{
    enable ? pluginManager->loadPlugin(plugin) : pluginManager->unloadPlugin(plugin);
}

