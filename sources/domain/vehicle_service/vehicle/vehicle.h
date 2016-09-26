#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>

namespace domain
{
    class Vehicle: public QObject // TODO: system hierarchy
    {
        Q_OBJECT

    public:
        explicit Vehicle(QObject* parent = nullptr);

    };
}

#endif // VEHICLE_H
