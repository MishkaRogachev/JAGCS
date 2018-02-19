#include "vehicles_sorting_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicles_model.h"

using namespace presentation;

VehiclesSortingModel::VehiclesSortingModel(QObject* paret):
    QSortFilterProxyModel(paret),
    m_showOffline(true)
{
    this->setFilterRole(VehiclesModel::VehicleOnlineRole);
    this->setSortRole(VehiclesModel::VehicleOnlineRole);

    this->setDynamicSortFilter(true);
    this->sort(0, Qt::AscendingOrder);
}

bool VehiclesSortingModel::showOffline() const
{
    return m_showOffline;
}

void VehiclesSortingModel::setShowOffline(bool showOffline)
{
    if (m_showOffline == showOffline) return;

    m_showOffline = showOffline;
    emit showOfflineChanged(m_showOffline);

    this->invalidate();
}

bool VehiclesSortingModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (m_showOffline)
    {
        bool leftOnline = this->sourceModel()->data(left, VehiclesModel::VehicleOnlineRole).toBool();
        bool rightOnline = this->sourceModel()->data(right, VehiclesModel::VehicleOnlineRole).toBool();

        if (leftOnline && !rightOnline) return true;
        if (!leftOnline && rightOnline) return false;
    }

    QString leftName = this->sourceModel()->data(left, VehiclesModel::VehicleNameRole).toString();
    QString rightName = this->sourceModel()->data(right, VehiclesModel::VehicleNameRole).toString();

    return leftName < rightName;
}

bool VehiclesSortingModel::filterAcceptsRow(int row, const QModelIndex& parent) const
{
    if (m_showOffline) return true;

    QModelIndex index = this->sourceModel()->index(row, 0, parent);
    return this->sourceModel()->data(index, VehiclesModel::VehicleOnlineRole).toBool();
}
