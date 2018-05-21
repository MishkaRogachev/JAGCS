#include "vehicle_list_sorting_model.h"

// Qt
#include <QDebug>

// Internal
#include "vehicle_list_model.h"

using namespace presentation;

VehicleListSortingModel::VehicleListSortingModel(QObject* paret):
    QSortFilterProxyModel(paret),
    m_showOffline(true)
{
    this->setFilterRole(VehicleListModel::VehicleOnlineRole);
    this->setSortRole(VehicleListModel::VehicleOnlineRole);

    this->setDynamicSortFilter(true);
    this->sort(0, Qt::AscendingOrder);
}

bool VehicleListSortingModel::showOffline() const
{
    return m_showOffline;
}

void VehicleListSortingModel::setShowOffline(bool showOffline)
{
    if (m_showOffline == showOffline) return;

    m_showOffline = showOffline;
    emit showOfflineChanged(m_showOffline);

    this->invalidate();
}

bool VehicleListSortingModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (m_showOffline)
    {
        bool leftOnline = this->sourceModel()->data(left, VehicleListModel::VehicleOnlineRole).toBool();
        bool rightOnline = this->sourceModel()->data(right, VehicleListModel::VehicleOnlineRole).toBool();

        if (leftOnline && !rightOnline) return true;
        if (!leftOnline && rightOnline) return false;
    }

    QString leftName = this->sourceModel()->data(left, VehicleListModel::VehicleNameRole).toString();
    QString rightName = this->sourceModel()->data(right, VehicleListModel::VehicleNameRole).toString();

    return leftName < rightName;
}

bool VehicleListSortingModel::filterAcceptsRow(int row, const QModelIndex& parent) const
{
    if (m_showOffline) return true;

    QModelIndex index = this->sourceModel()->index(row, 0, parent);
    return this->sourceModel()->data(index, VehicleListModel::VehicleOnlineRole).toBool();
}
