#ifndef VIBRATION_MODEL_H
#define VIBRATION_MODEL_H

// Qt
#include <QAbstractTableModel>
#include <QVector3D>

namespace presentation
{
    struct Vibration
    {
        int timestamp = 0;
        QVector3D data;
    };

    class VibrationModel: public QAbstractTableModel
    {
        Q_OBJECT

        Q_PROPERTY(int minTime READ minTime NOTIFY boundsChanged)
        Q_PROPERTY(int maxTime READ maxTime NOTIFY boundsChanged)
        Q_PROPERTY(float maxValue READ maxValue NOTIFY boundsChanged)

    public:
        explicit VibrationModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;

        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        int minTime() const;
        int maxTime() const;
        float maxValue() const;

    public slots:
        void addData(const Vibration& vibration);
        void resetData(const QList<Vibration>& data);

    signals:
        void boundsChanged();

    private:
        QList<Vibration> m_data;
        int m_minTime = 0;
        int m_maxTime = 0;
        float m_maxValue = 0;
    };
}

#endif // VIBRATION_MODEL_H
