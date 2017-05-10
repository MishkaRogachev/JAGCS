#ifndef MISSION_LINE_MAP_ITEM_MODEL_H
#define MISSION_LINE_MAP_ITEM_MODEL_H

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
    class MissionLineMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum MissionLineMapItemRoles
        {
            MissionPathRole = Qt::UserRole + 1,
        };

        explicit MissionLineMapItemModel(domain::MissionService* service,
                                         QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void onMissionAdded(const db::MissionPtr& mission);
        void onMissionRemoved(const db::MissionPtr& mission);
        void onMissionItemChanged(const db::MissionItemPtr& item);

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex missionIndex(const db::MissionPtr& mission) const;

    private:
        domain::MissionService* m_service;
        db::MissionPtrList m_missions;
    };
}

#endif // MISSION_LINE_MAP_ITEM_MODEL_H
