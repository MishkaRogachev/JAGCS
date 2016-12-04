#ifndef MISSION_MAP_ITEM_MODEL_H
#define MISSION_MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

namespace domain
{
    class MissionService;
}

namespace presentation
{
    class MissionMapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum VehicleMapItemRoles
        {
            MissionLineRole = Qt::UserRole + 1
        };

        MissionMapItemModel(domain::MissionService* service,
                            QObject* parent = nullptr);
        ~MissionMapItemModel() override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

    private slots:
        void onMissionAdded(uint8_t id);
        void onMissionRemoved(uint8_t id);

        void onMissionItemsChanged();

    protected:
        QHash<int, QByteArray> roleNames() const override;

        QModelIndex missionIndex(uint8_t id) const;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_MAP_ITEM_MODEL_H
