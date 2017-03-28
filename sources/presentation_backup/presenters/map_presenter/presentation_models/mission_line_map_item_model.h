#ifndef MISSION_LINE_MAP_ITEM_MODEL_H
#define MISSION_LINE_MAP_ITEM_MODEL_H

#include <QAbstractListModel>

namespace domain
{
    class Mission;
}

namespace presentation
{
    class MissionLineMapItemModel: public QAbstractListModel // TODO: refactor models
    {
        Q_OBJECT

    public:
        enum MissionLineMapItemRoles
        {
            MissionPathRole = Qt::UserRole + 1,
            MissionActualRole
        };

        MissionLineMapItemModel(QObject* parent = nullptr);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

        const QList<domain::Mission*>& missions() const;

    public slots:
        void addMission(domain::Mission* mission);
        void removeMission(domain::Mission* mission);

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex missionIndex(domain::Mission* mission) const;

    private slots:
        void updateMissionItems(domain::Mission* mission);
        void updateMissionPath(domain::Mission* mission);
        void onMissionItemPositionChanged();
        void onMissionStatusChanged();

    private:
        QList<domain::Mission*> m_missions;
    };
}

#endif // MISSION_LINE_MAP_ITEM_MODEL_H
