#include "link_list_model.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"

using namespace presentation;

LinkListModel::LinkListModel(QObject* parent):
    QAbstractListModel(parent)
{}

int LinkListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_links.count();
}

QVariant LinkListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_links.count()) return QVariant();

    dto::LinkDescriptionPtr link = m_links.at(index.row());

    switch (role)
    {
    case LinkIdRole: return link->id();
    case LinkNameRole: return link->name();
    default: return QVariant();
    }
}

void LinkListModel::setLinks(const dto::LinkDescriptionPtrList& links)
{
    this->beginResetModel();
    m_links = links;
    this->endResetModel();
}

void LinkListModel::addLink(const dto::LinkDescriptionPtr& link)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_links.append(link);
    this->endInsertRows();
}

void LinkListModel::updateLink(const dto::LinkDescriptionPtr& link)
{
    QModelIndex index = this->index(m_links.indexOf(link));
    if (!index.isValid()) return;

    emit dataChanged(index, index, { LinkNameRole });
}

void LinkListModel::removeLink(const dto::LinkDescriptionPtr& link)
{
    int row = m_links.indexOf(link);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_links.removeOne(link);
    this->endRemoveRows();
}

QHash<int, QByteArray> LinkListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[LinkIdRole] = "linkId";
    roles[LinkNameRole] = "linkName";

    return roles;
}
