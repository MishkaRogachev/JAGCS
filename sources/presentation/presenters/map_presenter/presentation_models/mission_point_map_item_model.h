#ifndef MISSION_POINT_MAP_ITEM_MODEL_H
#define MISSION_POINT_MAP_ITEM_MODEL_H

#include <QAbstractListModel>

namespace domain
{
    class MissionItem;
}

namespace presentation
{
    class MissionPointMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum MissionPointMapItemRoles
        {
            ItemCoordinateRole = Qt::UserRole + 1,
            ItemSequenceRole
        };

        MissionPointMapItemModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void addMissionItem(domain::MissionItem* item);
        void removeMissionItem(domain::MissionItem* item);

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex missionItemIndex(domain::MissionItem* item) const;

    private slots:
        void onCommandChanged();
        void onCoordinateChanged();

    private:
        QList<domain::MissionItem*> m_items;
    };
}

#endif // MISSION_POINT_MAP_ITEM_MODEL_H
