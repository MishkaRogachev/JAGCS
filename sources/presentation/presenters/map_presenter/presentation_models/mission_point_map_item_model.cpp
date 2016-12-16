#include "mission_point_map_item_model.h"

// Qt
#include <QGeoCoordinate>
#include <QDebug>

// Internal
#include "mission_item.h"

using namespace presentation;

MissionPointMapItemModel::MissionPointMapItemModel(QObject* parent):
    QAbstractListModel(parent)
{}

int MissionPointMapItemModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_items.count();
}

QVariant MissionPointMapItemModel::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) return QVariant();

    domain::MissionItem* item = m_items.at(index.row());

    switch (role)
    {
    case ItemCoordinateRole:
    {
        QGeoCoordinate coordinate(item->latitude(), item->longitude());
        return QVariant::fromValue(coordinate);
    }
    case ItemSequenceRole:
        return QVariant::fromValue(item->sequence());
    default:
        return QVariant();
    }
}

void MissionPointMapItemModel::addMissionItem(domain::MissionItem* item)
{
    this->beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());

    m_items.append(item);

    connect(item, &domain::MissionItem::latitudeChanged,
            this, &MissionPointMapItemModel::onCoordinateChanged);
    connect(item, &domain::MissionItem::longitudeChanged,
            this, &MissionPointMapItemModel::onCoordinateChanged);

    this->endInsertRows();
}

void MissionPointMapItemModel::removeMissionItem(domain::MissionItem* item)
{
    int row = m_items.indexOf(item);
    if (row == -1) return;

    this->beginRemoveRows(QModelIndex(), row, row);
    m_items.removeOne(item);

    this->endRemoveRows();

    emit dataChanged(this->index(row), this->index(m_items.count() - 1),
    { ItemSequenceRole });
}

QHash<int, QByteArray> MissionPointMapItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ItemCoordinateRole] = "itemCoordinate";
    roles[ItemSequenceRole] = "itemSeq";

    return roles;
}

QModelIndex MissionPointMapItemModel::missionItemIndex(
        domain::MissionItem* item) const
{
    return this->index(m_items.indexOf(item));
}

void MissionPointMapItemModel::onCoordinateChanged()
{
    QModelIndex index = this->missionItemIndex(
                            qobject_cast<domain::MissionItem*>(this->sender()));
    if (index.isValid()) emit dataChanged(index, index, { ItemCoordinateRole });
}
