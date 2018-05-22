#ifndef MISSION_LIST_FILTER_MODEL_H
#define MISSION_LIST_FILTER_MODEL_H

// Qt
#include <QSortFilterProxyModel>

namespace presentation
{
    class MissionListFilterModel: public QSortFilterProxyModel
    {
        Q_OBJECT

    public:
        explicit MissionListFilterModel(QObject* paret = nullptr);

    public slots:
        void filter(const QString& filterString);

    protected:
        bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
    };
}

#endif // MISSION_LIST_FILTER_MODEL_H
