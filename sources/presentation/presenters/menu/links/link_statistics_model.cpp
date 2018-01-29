#include "link_statistics_model.h"

// Qt
#include <QMap>
#include <QColor>
#include <QDebug>

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
    default:
        return QVariant();
    }
}

int LinkStatisticsModel::maxTime() const
{
    return m_data.count() - 1;
}

int LinkStatisticsModel::maxValue() const
{
    return m_maxValue * 1.2; // +20%
}

void LinkStatisticsModel::addData(int received, int sent)
{
    this->beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + 1);

    m_data.append(QPoint(received, sent));

    this->endInsertRows();

    if (m_maxValue < received) m_maxValue = received;
    if (m_maxValue < sent) m_maxValue = sent;

    emit boundsChanged();
}
