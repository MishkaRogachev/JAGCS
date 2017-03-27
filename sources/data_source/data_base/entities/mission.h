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
        Mission(int id = 0);

        static QString tableName();

        QString name() const;
        void setName(const QString& name);

        int count() const;

        const MissionItemPtrList& items() const;
        MissionItemPtrList& items();
        MissionItemPtr item(int index) const;

        void appendItem(const MissionItemPtr& item);
        MissionItemPtr takeItem(int index);
        MissionItemPtr takeLast();
        void insertItem(int index, const MissionItemPtr& item);
        void setItem(int index, const MissionItemPtr& item);

        void exchangePosition(int first, int last);
        void moveUp(int index);
        void moveDown(int index);

        void fixSequenceOrder();
        void setCount(int count);

        MissionAssignmentPtr assignment() const;
        void setAssignment(const MissionAssignmentPtr& assignment);

    private:
        QString m_name;
        MissionItemPtrList m_items;
        MissionAssignmentPtr m_assignment;
    };
}

#endif // MISSION_H
