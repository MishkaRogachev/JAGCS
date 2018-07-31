#include "plugins_list_model.h"

// Qt
#include <QDebug>

//QJsonObject({
//                "IID":"data_source.AbstractCommunicator",
//                "MetaData":{"dependencies":[],
//                            "description":"MAVLink communication protocol example",
//                            "interface":"data_source.AbstractCommunicator",
//                            "name":"MAVLink",
//                            "version":"0.0.1"
//                },
//                "className":"MavLinkCommunicator",
//                "debug":true,
//                "version":329989
//            })

namespace
{
    const QString metaData = "MetaData";
    const QString name = "name";
    const QString description = "description";
    const QString version = "version";
    const QString dependencies = "dependencies";
}

using namespace presentation;

PluginsListModel::PluginsListModel(QObject* parent):
    QAbstractListModel(parent)
{}

int PluginsListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_plugins.count();
}

QVariant PluginsListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_plugins.count()) return QVariant();

    QJsonObject object = m_plugins.values().at(index.row());
    QJsonObject meta = object.value(::metaData).toObject();

    switch (role)
    {
    case PluginNameRole:
        return meta.value(::name);
    case PluginDescriptionRole:
        return meta.value(::description);
    case PluginVersionRole:
        return meta.value(::version);
    case PluginDependenciesRole:
        return meta.value(::dependencies);
    case PluginEnabledRole:
        return object.value(::enabled);
    default: return QVariant();
    }
}

bool PluginsListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || index.row() >= m_plugins.count()) return false;

    if (role == PluginEnabledRole)
    {
        emit requestEnablePlugin(m_plugins.keys().at(index.row()), value.toBool());
        return true;
    }

    return QAbstractListModel::setData(index, value, role);
}

void PluginsListModel::setPlugin(const QString& plugin, const QJsonObject& data)
{
    if (m_plugins.contains(plugin))
    {
        QModelIndex index = this->index(m_plugins.keys().indexOf(plugin));
        if (!index.isValid()) return;

        m_plugins[plugin] = data;

        emit dataChanged(index, index, { PluginNameRole, PluginDescriptionRole, PluginVersionRole,
                                         PluginDependenciesRole, PluginEnabledRole } );
    }
    else
    {
        this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());

        m_plugins.insert(plugin, data);

        this->endInsertRows();
    }
}

void PluginsListModel::removePlugin(const QString& plugin)
{
    int row = m_plugins.keys().indexOf(plugin);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_plugins.remove(plugin);
    this->endRemoveRows();
}

QHash<int, QByteArray> PluginsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[PluginNameRole] = "pluginName";
    roles[PluginDescriptionRole] = "pluginDescription";
    roles[PluginVersionRole] = "pluginVersion";
    roles[PluginDependenciesRole] = "pluginDependencies";
    roles[PluginEnabledRole] = "pluginEnabled";

    return roles;
}
