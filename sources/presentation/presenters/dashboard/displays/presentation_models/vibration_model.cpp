#include "vibration_model.h"

// Qt
#include <QMap>
#include <QColor>
#include <QDebug>

namespace
{
    QMap<int, QColor> colors(
    {
                { 0, Qt::black },
                { 1, Qt::cyan },
                { 2, Qt::magenta },
                { 3, Qt::red }
    });
}

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

    return 4; // Time + Vector3D
}

QVariant VibrationModel::headerData(int section, Qt::Orientation orientation, int role) const
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
        if (index.column() == 0) return index.row();
        return m_data.at(index.row()).operator [](index.column() - 1);
    case Qt::BackgroundRole:
        return ::colors.value(index.column() + 1, Qt::white);
    default:
        return QVariant();
    }
}

void VibrationModel::addData(const QVector3D& newData)
{
    this->beginInsertRows(QModelIndex(), m_data.count(), m_data.count() + 1);

    m_data.append(newData);

    this->endInsertRows();
}
