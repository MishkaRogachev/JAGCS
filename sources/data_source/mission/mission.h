#ifndef MISSION_H
#define MISSION_H

// Qt
#include <QList>

namespace data_source
{
    class MissionItem;

    class Mission
    {
    public:
        Mission(int id);

        int id() const;

        QString name() const;
        void setName(const QString& name);

        const QList<MissionItem*>& items() const;
        MissionItem* item(int index) const;
        void addItem(MissionItem* item);
        void removeItem(int index);

    private:
        const int m_id;
        QString m_name;
        QList<MissionItem*> m_items;
    };
}

#endif // MISSION_H
