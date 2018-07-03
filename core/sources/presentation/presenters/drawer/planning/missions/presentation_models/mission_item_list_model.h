#ifndef MISSION_ITEM_LIST_MODEL_H
#define MISSION_ITEM_LIST_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dto_traits.h"

namespace presentation
{
    // TODO: merge with MissionPointMapItemModel
    class MissionItemListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum MissionItemListRoles
        {
            ItemIdRole = Qt::UserRole + 1,
            SequenceRole,
            CommandRole,
            ReachedRole,
            StatusRole
        };

        explicit MissionItemListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void setMissionItems(const dto::MissionItemPtrList& items);
        void addMissionItem(const dto::MissionItemPtr& item);
        void updateMissionItem(const dto::MissionItemPtr& item);
        void removeMissionItem(const dto::MissionItemPtr& item);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        dto::MissionItemPtrList m_items;
    };
}

#endif // MISSION_ITEM_LIST_MODEL_H
