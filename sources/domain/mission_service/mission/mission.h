#ifndef MISSION_H
#define MISSION_H

#include <QObject>

namespace domain
{
    class Mission: public QObject
    {
        Q_OBJECT

    public:
        explicit Mission(QObject* parent = nullptr);

    };
}

#endif // MISSION_H
