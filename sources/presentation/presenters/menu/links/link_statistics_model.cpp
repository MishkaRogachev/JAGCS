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
        if (index.column() == 0) return m_data.at(index.row()).timestamp;
        if (index.column() == 1) return m_data.at(index.row()).received;
        if (index.column() == 2) return m_data.at(index.row()).sent;
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

void LinkStatisticsModel::addData(const Statistics& statistics)
{
    this->beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + 1);
    m_data.append(statistics);
    this->endInsertRows();

    if (m_maxValue < statistics.received) m_maxValue = statistics.received;
    if (m_maxValue < statistics.sent) m_maxValue = statistics.sent;

    if (m_data.count() > settings::Provider::value(
            settings::communication::statisticsCount).toInt())
    {
       this->beginRemoveRows(QModelIndex(), 0, 0);
        m_data.removeFirst();
        this->endRemoveRows();
    }
    emit boundsChanged();
}

void LinkStatisticsModel::resetData(const QList<Statistics>& data)
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
    m_minTime = 0;
    for (const Statistics& statistics: m_data)
    {
        if (m_maxValue < statistics.received) m_maxValue = statistics.received;
        if (m_maxValue < statistics.sent) m_maxValue = statistics.sent;
    }

    emit boundsChanged();
}
