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

int LinkStatisticsModel::maxRecv() const
{
    return m_maxRecv * 1.2; // +20%
}

int LinkStatisticsModel::maxSent() const
{
    return m_maxSent * 1.2; // +20%
}

void LinkStatisticsModel::addData(const dto::LinkStatisticsPtr& statistics)
{
    if (m_data.isEmpty()) m_minTime = statistics->timestamp();

    this->beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + 1);
    m_data.append(dto::LinkStatisticsPtr(new dto::LinkStatistics(*statistics.data())));
    this->endInsertRows();

    if (m_maxTime < statistics->timestamp() || m_data.isEmpty()) m_maxTime = statistics->timestamp();
    if (m_maxRecv < statistics->bytesRecv() || m_data.isEmpty()) m_maxRecv = statistics->bytesRecv();
    if (m_maxSent < statistics->bytesSent() || m_data.isEmpty()) m_maxSent = statistics->bytesSent();

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

void LinkStatisticsModel::resetData(const dto::LinkStatisticsPtrList& data)
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

    m_minTime = m_data.isEmpty() ? 0 : m_data.first()->timestamp();
    m_maxTime = m_data.isEmpty() ? 0 : m_data.last()->timestamp();
    m_maxRecv = m_data.isEmpty() ? 0 : m_data.first()->bytesRecv();
    m_maxSent = m_data.isEmpty() ? 0 : m_data.first()->bytesSent();

    for (const dto::LinkStatisticsPtr& statistics: m_data)
    {
        if (m_maxRecv < statistics->bytesRecv()) m_maxRecv = statistics->bytesRecv();
        if (m_maxSent < statistics->bytesSent()) m_maxSent = statistics->bytesSent();
    }

    emit boundsChanged();
}
