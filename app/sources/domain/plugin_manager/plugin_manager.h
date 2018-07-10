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

        QList<QJsonObject> discoveredPlugins() const;

    public slots:
        void discoverPlugins();

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // PLUGIN_MANAGER_H
