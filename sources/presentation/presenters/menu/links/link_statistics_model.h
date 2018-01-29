#ifndef LINK_STATISTICS_MODEL_H
#define LINK_STATISTICS_MODEL_H

// Qt
#include <QAbstractTableModel>
#include <QPointF>

namespace presentation
{
    class LinkStatisticsModel: public QAbstractTableModel
    {
        Q_OBJECT

    public:
        explicit LinkStatisticsModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;

        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    public slots:
        void addData(float received, float sent);

    private:
        QList<QPointF> m_data;
    };
}

#endif // LINK_STATISTICS_MODEL_H
