#include "vibration_model.h"

// Qt
#include <QMap>
#include <QColor>
#include <QDebug>

// Internal
#include "settings_provider.h"

using namespace presentation;

VibrationModel::VibrationModel(QObject* parent):
    QAbstractTableModel(parent)
{}

int VibrationModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return m_data.count();
}

int VibrationModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return 4; // Time, X, Y, Z
}

QVariant VibrationModel::headerData(int section,
                                    Qt::Orientation orientation,
                                    int role) const
{
    if (role != Qt::DisplayPropertyRole) return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0: return tr("T");
        case 1: return tr("X");
        case 2: return tr("Y");
        case 3: return tr("Z");
        default: return QVariant();
        }
    }
    else
    {
        return QString("%1").arg(section + 1);
    }
}

QVariant VibrationModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 0) return m_data.at(index.row()).timestamp;
        if (index.column() == 1) return m_data.at(index.row()).data.x();
        if (index.column() == 2) return m_data.at(index.row()).data.y();
        if (index.column() == 3) return m_data.at(index.row()).data.z();
    default:
        return QVariant();
    }
}

int VibrationModel::minTime() const
{
    return m_minTime;
}

int VibrationModel::maxTime() const
{
    return m_maxTime;
}

float VibrationModel::maxValue() const
{
    return m_maxValue;
}

void VibrationModel::addData(const Vibration& vibration)
{
    if (m_data.isEmpty()) m_minTime = vibration.timestamp;

    this->beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + 1);
    m_data.append(vibration);
    this->endInsertRows();

    if (m_maxTime < vibration.timestamp) m_maxTime = vibration.timestamp;
    m_maxValue = qMax(m_maxValue, vibration.data.x());
    m_maxValue = qMax(m_maxValue, vibration.data.y());
    m_maxValue = qMax(m_maxValue, vibration.data.z());

    int count = qMax(2, settings::Provider::value(
                         settings::gui::vibrationModelCount).toInt());
    if (m_data.count() > count)
    {
        this->beginRemoveRows(QModelIndex(), 0, 0);
        m_data.removeFirst();
        this->endRemoveRows();

        m_minTime = m_data.first().timestamp;
    }

    emit boundsChanged();
}

void VibrationModel::resetData(const QList<Vibration>& data)
{
    this->beginResetModel();

    int maxCount = settings::Provider::value(
                       settings::gui::vibrationModelCount).toInt();

    if (data.count() <= maxCount)
    {
        m_data = data;
    }
    else
    {
        m_data = data.mid(0, maxCount);
    }

    this->endResetModel();

    m_minTime = m_data.isEmpty() ? 0 : m_data.first().timestamp;
    m_maxTime = m_data.isEmpty() ? 0 : m_data.last().timestamp;
    m_maxValue = 0;

    for (const Vibration& vibration: m_data)
    {
        m_maxValue = qMax(m_maxValue, vibration.data.x());
        m_maxValue = qMax(m_maxValue, vibration.data.y());
        m_maxValue = qMax(m_maxValue, vibration.data.z());
    }

    emit boundsChanged();
}
