#ifndef MISSION_LINE_MAP_ITEM_MODEL_H
#define MISSION_LINE_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "db_traits.h"

namespace db
{
    class DbFacade;
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

        explicit MissionLineMapItemModel(db::DbFacade* dbFacade, QObject* parent = nullptr);

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
        db::DbFacade* m_dbFacade;
        db::MissionPtrList m_missions;
    };
}

#endif // MISSION_LINE_MAP_ITEM_MODEL_H
