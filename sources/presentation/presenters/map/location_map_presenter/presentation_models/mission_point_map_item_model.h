#ifndef MISSION_POINT_MAP_ITEM_MODEL_H
#define MISSION_POINT_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dto_traits.h"

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
            ItemRole = Qt::UserRole + 1,
            ItemCoordinateRole,
            ItemVisibleRole,
            ItemAcceptanceRadius,
            ItemRadius,
            ItemIndex
        };

        explicit MissionPointMapItemModel(domain::MissionService* service,
                                          QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void onMissionItemAdded(const dto::MissionItemPtr& item);
        void onMissionItemRemoved(const dto::MissionItemPtr& item);
        void onMissionItemChanged(const dto::MissionItemPtr& item);
        void onMissionChanged(const dto::MissionPtr& mission);

    protected:
        QHash<int, QByteArray> roleNames() const override;
        QModelIndex itemIndex(const dto::MissionItemPtr& item) const;

    private:
        domain::MissionService* m_service;
        dto::MissionItemPtrList m_items;
    };
}

#endif // MISSION_POINT_MAP_ITEM_MODEL_H
