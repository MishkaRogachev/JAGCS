#include "mission_item_list_model.h"

// Qt
#include <QDebug>

// Internal
#include "mission_item.h"

using namespace presentation;

MissionItemListModel::MissionItemListModel(QObject* parent):
    QAbstractListModel(parent)
{}

int MissionItemListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_items.count();
}

QVariant MissionItemListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_items.count()) return QVariant();

    dto::MissionItemPtr item = m_items.at(index.row());
    if (!item) return QVariant();

    switch (role)
    {
    case ItemIdRole: return item->id();
    case SequenceRole: return item->sequence();
    case CommandRole: return item->command();
    case ReachedRole: return item->isReached();
    case StatusRole: return item->status();
    default: return QVariant();
    }
}

void MissionItemListModel::setMissionItems(const dto::MissionItemPtrList& items)
{
    this->beginResetModel();
    m_items = items;
    this->endResetModel();
}

void MissionItemListModel::addMissionItem(const dto::MissionItemPtr& item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_items.append(item);
    this->endInsertRows();
}

void MissionItemListModel::updateMissionItem(const dto::MissionItemPtr& item)
{
    QModelIndex index = this->index(m_items.indexOf(item));
    if (!index.isValid()) return;

    emit dataChanged(index, index);
}

void MissionItemListModel::removeMissionItem(const dto::MissionItemPtr& MissionItem)
{
    int row = m_items.indexOf(MissionItem);

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(MissionItem);
    this->endRemoveRows();
}

QHash<int, QByteArray> MissionItemListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ItemIdRole] = "itemId";
    roles[SequenceRole] = "sequence";
    roles[CommandRole] = "command";
    roles[ReachedRole] = "reached";
    roles[StatusRole] = "status";

    return roles;
}
