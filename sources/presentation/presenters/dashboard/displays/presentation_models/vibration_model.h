#ifndef VIBRATION_MODEL_H
#define VIBRATION_MODEL_H

// Qt
#include <QAbstractTableModel>
#include <QVector3D>

namespace presentation
{
    class VibrationModel: public QAbstractTableModel
    {
        Q_OBJECT

    public:
        explicit VibrationModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;

        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    public slots:
        void addData(const QVector3D& newData);

    private:
        QList<QVector3D> m_data;
    };
}

#endif // VIBRATION_MODEL_H
