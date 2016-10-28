#ifndef MAP_ITEM_MODEL_H
#define MAP_ITEM_MODEL_H

// Qt
#include <QAbstractListModel>

// Internal
#include "map_item.h"

namespace presentation
{
    class MapItemModel: public QAbstractListModel
    {
        Q_OBJECT

    public:
        enum MapItemRoles
        {
            PositionRole = Qt::UserRole + 1,
            DirectionRole,
            MarkRole
        };

        MapItemModel(QObject* parent = nullptr);
        ~MapItemModel() override;

        void addMapItem(MapItem* item);
        void removeMapItem(MapItem* item);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index,
                      int role = Qt::DisplayRole) const override;

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        QList<MapItem*> m_items;
    };
}

#endif // MAP_ITEM_MODEL_H
