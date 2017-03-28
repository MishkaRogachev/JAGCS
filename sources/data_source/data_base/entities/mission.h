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

        void setId(int id) override;

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
        void clearItems();

        void exchangePosition(int first, int last);
        void moveUp(int index);
        void moveDown(int index);

        void fixSequenceOrder();
        void setCount(int count);

    private:
        QString m_name;
        MissionItemPtrList m_items;
    };
}

#endif // MISSION_H
