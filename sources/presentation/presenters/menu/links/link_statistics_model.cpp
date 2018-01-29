#include "link_statistics_model.h"

// Qt
#include <QMap>
#include <QColor>
#include <QDebug>

namespace
{
    QMap<int, QColor> colors(
    {
        { 1, "#CDDC39" },
        { 2, "#18FFFF" }
    });
}

using namespace presentation;

LinkStatisticsModel::LinkStatisticsModel(QObject* parent):
    QAbstractTableModel(parent)
{}

int LinkStatisticsModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_data.count();
}

int LinkStatisticsModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return 3; // Time, Recv, Sent
}

QVariant LinkStatisticsModel::headerData(int section,
                                         Qt::Orientation orientation,
                                         int role) const
{
    if (role != Qt::DisplayPropertyRole) return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0: return tr("T");
        case 1: return tr("Recv");
        case 2: return tr("Sent");
        default: return QVariant();
        }
    }
    else
    {
        return QString("%1").arg(section + 1);
    }
}

QVariant LinkStatisticsModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 0) return index.row();
        if (index.column() == 1) return m_data.at(index.row()).x();
        if (index.column() == 2) return m_data.at(index.row()).y();
        return QVariant();
    case Qt::BackgroundRole:
        return ::colors.value(index.column() + 1, Qt::white);
    default:
        return QVariant();
    }
}

void LinkStatisticsModel::addData(float received, float sent)
{
    this->beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + 1);

    m_data.append(QPointF(received, sent));

    this->endInsertRows();
}
