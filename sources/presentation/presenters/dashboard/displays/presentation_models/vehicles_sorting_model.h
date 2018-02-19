#ifndef VEHICLES_SORTING_MODEL_H
#define VEHICLES_SORTING_MODEL_H

// Qt
#include <QSortFilterProxyModel>

namespace presentation
{
    class VehiclesSortingModel: public QSortFilterProxyModel
    {
        Q_OBJECT

        Q_PROPERTY(bool showOffline READ showOffline WRITE setShowOffline NOTIFY showOfflineChanged)

    public:
        explicit VehiclesSortingModel(QObject* paret = nullptr);

        bool showOffline() const;

    public slots:
        void setShowOffline(bool showOffline);

    signals:
        void showOfflineChanged(bool showOffline);

    protected:
        bool lessThan(const QModelIndex& left, const QModelIndex& right) const;
        bool filterAcceptsRow(int row, const QModelIndex& parent);

    private:
        bool m_showOffline;
    };
}

#endif // VEHICLES_SORTING_MODEL_H
