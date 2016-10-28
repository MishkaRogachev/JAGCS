#include "map_item_model.h"

using namespace presentation;

MapItemModel::MapItemModel(QObject* parent):
    QAbstractListModel(parent)
{}

MapItemModel::~MapItemModel()
{
    while (!m_items.isEmpty())
        delete m_items.takeFirst();
}

void MapItemModel::addMapItem(MapItem* item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
    m_items << item;
    this->endInsertRows();
}

void MapItemModel::removeMapItem(MapItem* item)
{
    int row = m_items.indexOf(item);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);
    this->endRemoveRows();
}

int MapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant MapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) return QVariant();

    MapItem* item = m_items.at(index.row());

    switch (role)
    {
    case PositionRole:
        return QVariant::fromValue(item->position());
    case DirectionRole:
        return item->direction();
    case MarkRole:
        return item->mark();
    // TODO: other roles
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[PositionRole] = "position";
    roles[DirectionRole] = "direction";
    roles[MarkRole] = "mark";

    return roles;
}
