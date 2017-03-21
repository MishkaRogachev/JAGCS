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

        int count() const;

        const MissionItemPtrList& items() const;
        MissionItemPtrList& items();
        MissionItemPtr item(int index) const;

        void addItem(const MissionItemPtr& item);
        MissionItemPtr takeItem(int index);
        void insertItem(int index,const MissionItemPtr& item);

        void fixSequenceOrder();

    private:
        QString m_name;
        MissionItemPtrList m_items;
    };
}

#endif // MISSION_H
