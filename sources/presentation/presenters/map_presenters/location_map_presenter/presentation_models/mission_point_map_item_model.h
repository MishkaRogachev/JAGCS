#ifndef MISSION_POINT_MAP_ITEM_MODEL_H
#define MISSION_POINT_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "db_traits.h"

namespace domain
{
    class MissionService;
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
            ItemSequenceRole,
            ItemIconRole,
            ItemAcceptanceRadius,
            ItemRadius,
            ItemCurrent
        };

        explicit MissionPointMapItemModel(domain::MissionService* service,
                                          QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void onMissionItemAdded(const db::MissionItemPtr& item);
        void onMissionItemRemoved(const db::MissionItemPtr& item);
        void onMissionItemChanged(const db::MissionItemPtr& item);

    protected:
        QHash<int, QByteArray> roleNames() const override;
        QModelIndex itemIndex(const db::MissionItemPtr& item) const;

    private:
        domain::MissionService* m_service;
        db::MissionItemPtrList m_items;
    };
}

#endif // MISSION_POINT_MAP_ITEM_MODEL_H
