#ifndef VEHICLES_SORTING_MODEL_H
#define VEHICLES_SORTING_MODEL_H

// Qt
#include <QSortFilterProxyModel>

namespace presentation
{
    class VehiclesSortingModel: public QSortFilterProxyModel
    {
        Q_OBJECT

        Q_PROPERTY(bool onlineOnTop READ onlineOnTop WRITE setOnlineOnTop NOTIFY onlineOnTopChanged)

    public:
        explicit VehiclesSortingModel(QObject* paret = nullptr);

        bool onlineOnTop() const;

    public slots:
        void setOnlineOnTop(bool onlineOnTop);

    signals:
        void onlineOnTopChanged(bool onlineOnTop);

    protected:
        bool lessThan(const QModelIndex& left, const QModelIndex& right) const;

    private:
        bool m_onlineOnTop;
    };
}

#endif // VEHICLES_SORTING_MODEL_H
