#ifndef PLUGINS_LIST_MODEL_H
#define PLUGINS_LIST_MODEL_H

// Qt
#include <QAbstractListModel>
#include <QJsonObject>

namespace
{
    const QString enabled = "enabled";
}

namespace presentation
{
    class PluginsListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum PluginsListRoles
        {
            PluginNameRole = Qt::UserRole + 1,
            PluginDescriptionRole,
            PluginVersionRole,
            PluginDependenciesRole,
            PluginEnabledRole
        };

        explicit PluginsListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void addPluginData(const QString& plugin, const QJsonObject& data);
        void removePlugin(const QString& plugin);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        QMap<QString, QJsonObject> m_plugins;
    };
}

#endif // PLUGINS_LIST_MODEL_H
