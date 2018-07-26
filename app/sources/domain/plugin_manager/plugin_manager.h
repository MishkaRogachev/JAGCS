#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

// Qt
#include <QObject>
#include <QJsonObject>

namespace domain
{
    class PluginManager: public QObject
    {
        Q_OBJECT

    public:
        explicit PluginManager(QObject* parent = nullptr);
        ~PluginManager() override;

        static PluginManager* instance();

        QStringList discoveredPlugins() const;
        QStringList loadedPlugins() const;

        QJsonObject pluginMetaData(const QString& plugin) const;

    public slots:
        void discoverPlugins();

        void loadPlugin(const QString& plugin);
        void unloadPlugin(const QString& plugin);

        void saveConfiguration();
        void restoreConfiguration();

    signals:
        void pluginDiscovered(QString plugin);
        void pluginLoaded(QString plugin);
        void pluginUnloaded(QString plugin);

    private:
        static PluginManager* lastCreatedManager;

        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#define pluginManager (domain::PluginManager::instance())

#endif // PLUGIN_MANAGER_H
