#ifndef MISSION_POINT_MAP_ITEM_MODEL_H
#define MISSION_POINT_MAP_ITEM_MODEL_H

#include <QAbstractListModel>

namespace domain
{
    class AbstractMissionItem;
}

namespace presentation
{
    // TODO: Replace with MissionMapModel with dynamic MapItemViews
    class MissionPointMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum MissionPointMapItemRoles
        {
            ItemCoordinateRole = Qt::UserRole + 1,
            ItemSequenceRole,
            ItemIconRole,
            ItemAcceptanceRadius,
            ItemRadius,
            ItemCurrent
        };

        MissionPointMapItemModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void addMissionItem(domain::AbstractMissionItem* item);
        void removeMissionItem(domain::AbstractMissionItem* item);
        void setMissionItems(const QList<domain::AbstractMissionItem*>& items);
        void clearMissionItems();

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex missionItemIndex(domain::AbstractMissionItem* item) const;

    private slots:
        void onCommandChanged();
        void onCoordinateChanged();
        void onAcceptanceRadiusChanged();
        void onRadiusChanged();
        void onCurrentChanged();

    private:
        QList<domain::AbstractMissionItem*> m_items;
    };
}

#endif // MISSION_POINT_MAP_ITEM_MODEL_H
