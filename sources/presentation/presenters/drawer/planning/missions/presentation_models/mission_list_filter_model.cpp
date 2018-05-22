#include "mission_list_filter_model.h"

// Qt
#include <QDebug>

// Internal
#include "mission_list_model.h"

using namespace presentation;

MissionListFilterModel::MissionListFilterModel(QObject* paret):
    QSortFilterProxyModel(paret)
{
    this->setFilterRole(MissionListModel::MissionNameRole);
    this->setSortRole(MissionListModel::MissionNameRole);

    this->setDynamicSortFilter(true);
    this->sort(0, Qt::AscendingOrder);
}

void MissionListFilterModel::filter(const QString& filterString)
{
    this->setFilterFixedString(filterString);
}

bool MissionListFilterModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QString leftName = this->sourceModel()->data(left, this->sortRole()).toString();
    QString rightName = this->sourceModel()->data(right, this->sortRole()).toString();

    return leftName < rightName;
}
