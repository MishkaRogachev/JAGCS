#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

// Qt
#include <QObject>

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

    public slots:
        void discoverPlugins();

    private:
        static PluginManager* lastCreatedManager;

        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#define pluginManager (domain::PluginManager::instance())

#endif // PLUGIN_MANAGER_H
