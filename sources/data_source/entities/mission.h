#ifndef MISSION_H
#define MISSION_H

// Internal
#include "base_entity.h"

namespace data_source
{
    class Mission: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)

    public:
        Mission(IdentityMap* iMap);

        static QString tableName();

        QString name() const;
        void setName(const QString& name);

        const MissionItemPtrList& items() const;
        MissionItemPtrList& items();
        MissionItemPtr item(int index) const;
        void addItem(MissionItemPtr item);
        void removeItem(int index);

    private:
        QString m_name;
        MissionItemPtrList m_items;
    };
}

#endif // MISSION_H
