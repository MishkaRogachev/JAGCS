#include "link_statistics_model.h"

// Qt
#include <QMap>
#include <QColor>
#include <QDebug>

// Internal
#include "settings_provider.h"

#include "link_statistics.h"

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
        if (index.column() == 0) return m_data.at(index.row())->timestamp();
        if (index.column() == 1) return m_data.at(index.row())->bytesRecv();
        if (index.column() == 2) return m_data.at(index.row())->bytesSent();
        return QVariant();
    default:
        return QVariant();
    }
}

int LinkStatisticsModel::minTime() const
{
    return m_minTime;
}

int LinkStatisticsModel::maxTime() const
{
    return m_maxTime;
}

int LinkStatisticsModel::maxValue() const
{
    return m_maxValue * 1.2; // +20%
}

void LinkStatisticsModel::addData(const dao::LinkStatisticsPtr& statistics)
{
    int maxValue = qMax(statistics->bytesRecv(), statistics->bytesSent());
    if (m_maxValue < maxValue || m_data.isEmpty()) m_maxValue = maxValue;
    if (m_data.isEmpty()) m_minTime = statistics->timestamp();
    if (m_maxTime < statistics->timestamp() || m_data.isEmpty()) m_maxTime = statistics->timestamp();

    this->beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + 1);
    m_data.append(dao::LinkStatisticsPtr(new dao::LinkStatistics(*statistics.data())));
    this->endInsertRows();

    int count = qMax(2, settings::Provider::value(settings::communication::statisticsCount).toInt());
    if (m_data.count() > count)
    {
        this->beginRemoveRows(QModelIndex(), 0, 0);
        m_data.removeFirst();
        this->endRemoveRows();

        m_minTime = m_data.first()->timestamp();
    }

    emit boundsChanged();
}

void LinkStatisticsModel::resetData(const dao::LinkStatisticsPtrList& data)
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

    m_maxValue = m_data.isEmpty() ? 0 : qMax(m_data.first()->bytesRecv(),
                                             m_data.first()->bytesSent());
    m_minTime = m_data.isEmpty() ? 0 : m_data.first()->timestamp();
    m_maxTime = m_data.isEmpty() ? 0 : m_data.last()->timestamp();

    for (const dao::LinkStatisticsPtr& statistics: m_data)
    {
        if (m_maxValue < statistics->bytesRecv()) m_maxValue = statistics->bytesRecv();
        if (m_maxValue < statistics->bytesSent()) m_maxValue = statistics->bytesSent();
    }

    emit boundsChanged();
}
