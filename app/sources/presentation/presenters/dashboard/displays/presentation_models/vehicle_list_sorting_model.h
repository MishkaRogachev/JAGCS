#ifndef VEHICLE_LIST_SORTING_MODEL_H
#define VEHICLE_LIST_SORTING_MODEL_H

// Qt
#include <QSortFilterProxyModel>

namespace presentation
{
    class VehicleListSortingModel: public QSortFilterProxyModel
    {
        Q_OBJECT

        Q_PROPERTY(bool showOffline READ showOffline WRITE setShowOffline NOTIFY showOfflineChanged)

    public:
        explicit VehicleListSortingModel(QObject* paret = nullptr);

        bool showOffline() const;

    public slots:
        void setShowOffline(bool showOffline);

    signals:
        void showOfflineChanged(bool showOffline);

    protected:
        bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
        bool filterAcceptsRow(int row, const QModelIndex& parent) const override;

    private:
        bool m_showOffline;
    };
}

#endif // VEHICLE_LIST_SORTING_MODEL_H
