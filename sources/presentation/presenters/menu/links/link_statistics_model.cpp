#include "link_statistics_model.h"

// Qt
#include <QMap>
#include <QColor>
#include <QDebug>

// Internal
#include "settings_provider.h"

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

    if (m_data.count() > settings::Provider::value(
            settings::communication::statisticsCount).toInt())
    {
       this->beginRemoveRows(QModelIndex(), 0, 0);
        m_data.removeFirst();
        this->endRemoveRows();
    }

    qDebug() << received << sent << m_data.count();

    emit boundsChanged();
}

void LinkStatisticsModel::resetData(const QList<QPoint>& data)
{
    this->beginResetModel();

    int maxCount = settings::Provider::value(
                       settings::communication::statisticsCount).toInt();

    if (data.count() < maxCount)
    {
        m_data = data;
    }
    else
    {
        m_data = data.mid(0, maxCount);
    }

    this->endResetModel();

    m_maxValue = 0;
    for (const QPoint& point : m_data)
    {
        if (m_maxValue < point.x()) m_maxValue = point.x();
        if (m_maxValue < point.y()) m_maxValue = point.y();
    }

    emit boundsChanged();
}
