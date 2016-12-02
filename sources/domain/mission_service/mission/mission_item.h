#ifndef MISSION_ITEM_H
#define MISSION_ITEM_H

#include <QObject>

namespace domain
{
    class MissionItem: public QObject
    {
        Q_OBJECT

    public:
        explicit MissionItem(QObject* parent = nullptr);

    };
}

#endif // MISSION_ITEM_H
