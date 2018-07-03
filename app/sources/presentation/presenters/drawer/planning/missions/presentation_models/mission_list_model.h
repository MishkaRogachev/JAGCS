#ifndef MISSION_LIST_MODEL_H
#define MISSION_LIST_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "dto_traits.h"

namespace presentation
{
    class MissionListModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum MissionListRoles
        {
            MissionIdRole = Qt::UserRole + 1,
            MissionNameRole,
        };

        explicit MissionListModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    public slots:
        void setMissions(const dto::MissionPtrList& missions);
        void addMission(const dto::MissionPtr& mission);
        void updateMission(const dto::MissionPtr& mission);
        void removeMission(const dto::MissionPtr& mission);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        dto::MissionPtrList m_missions;
    };
}

#endif // MISSION_LIST_MODEL_H
