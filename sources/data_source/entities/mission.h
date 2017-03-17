#ifndef MISSION_H
#define MISSION_H

// Internal
#include "base_entity.h"

namespace data_source
{
    class MissionItem;

    class Mission: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)

    public:
        Mission(int id);

        static QString tableName();

        QString name() const;
        void setName(const QString& name);

        const QList<MissionItem*>& items() const;
        MissionItem* item(int index) const;
        void addItem(MissionItem* item);
        void removeItem(int index);

    private:
        QString m_name;
        QList<MissionItem*> m_items;
    };
}

#endif // MISSION_H
