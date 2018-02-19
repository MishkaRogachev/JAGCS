#include "vehicles_sorting_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicles_model.h"

using namespace presentation;

VehiclesSortingModel::VehiclesSortingModel(QObject* paret):
    QSortFilterProxyModel(paret),
    m_onlineOnTop(true)
{}

bool VehiclesSortingModel::onlineOnTop() const
{
    return m_onlineOnTop;
}

void VehiclesSortingModel::setOnlineOnTop(bool onlineOnTop)
{
    if (m_onlineOnTop == onlineOnTop) return;

    m_onlineOnTop = onlineOnTop;
    emit onlineOnTopChanged(m_onlineOnTop);
}

bool VehiclesSortingModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QString leftName = sourceModel()->data(left, VehiclesModel::VehicleNameRole).toString();
    QString rightName = sourceModel()->data(right, VehiclesModel::VehicleNameRole).toString();

    if (m_onlineOnTop)
    {
        bool leftOnline = sourceModel()->data(left, VehiclesModel::VehicleNameRole).toBool();
        bool rightOnline = sourceModel()->data(right, VehiclesModel::VehicleNameRole).toBool();

        if (leftOnline && !rightOnline) return true;
        if (!leftOnline && rightOnline) return false;
    }

    return leftName < rightName;
}
