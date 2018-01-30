#ifndef LINK_STATISTICS_MODEL_H
#define LINK_STATISTICS_MODEL_H

// Qt
#include <QAbstractTableModel>
#include <QPoint>

namespace presentation
{
    class LinkStatisticsModel: public QAbstractTableModel
    {
        Q_OBJECT

        Q_PROPERTY(int maxTime READ maxTime NOTIFY boundsChanged)
        Q_PROPERTY(int maxValue READ maxValue NOTIFY boundsChanged)

    public:
        explicit LinkStatisticsModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;

        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        int maxTime() const;
        int maxValue() const;

    public slots:
        void addData(int received, int sent);
        void resetData(const QList<QPoint>& data);

    signals:
        void boundsChanged();

    private:
        QList<QPoint> m_data;
        int m_maxValue = 0;
    };
}

#endif // LINK_STATISTICS_MODEL_H
