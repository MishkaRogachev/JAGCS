#ifndef LINK_STATISTICS_MODEL_H
#define LINK_STATISTICS_MODEL_H

// Qt
#include <QAbstractTableModel>

// Internal
#include "dao_traits.h"

namespace presentation
{
    class LinkStatisticsModel: public QAbstractTableModel
    {
        Q_OBJECT

        Q_PROPERTY(int minTime READ minTime NOTIFY boundsChanged)
        Q_PROPERTY(int maxTime READ maxTime NOTIFY boundsChanged)
        Q_PROPERTY(int maxValue READ maxValue NOTIFY boundsChanged)

    public:
        explicit LinkStatisticsModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;

        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        int minTime() const;
        int maxTime() const;
        int maxValue() const;

    public slots:
        void addData(const dao::LinkStatisticsPtr& statistics);
        void resetData(const dao::LinkStatisticsPtrList& data);

    signals:
        void boundsChanged();

    private:
        dao::LinkStatisticsPtrList m_data;
        int m_maxValue = 0;
        int m_maxTime = 0;
        int m_minTime = 0;
    };
}

#endif // LINK_STATISTICS_MODEL_H
