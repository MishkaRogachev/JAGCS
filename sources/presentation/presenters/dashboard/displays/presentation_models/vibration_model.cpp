#include "vibration_model.h"

// Qt
#include <QMap>
#include <QColor>
#include <QDebug>

namespace
{
    QMap<int, QColor> colors(
    {
                { 0, Qt::cyan },
                { 1, Qt::magenta },
                { 2, Qt::red }
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

    return 3; // Vector3D
}

QVariant VibrationModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayPropertyRole) return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0: return tr("X");
        case 1: return tr("Y");
        case 2: return tr("Z");
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
        return m_data.at(index.row()).operator [](index.column());
    case Qt::BackgroundRole:
        return ::colors.value(index.column(), Qt::white);
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
