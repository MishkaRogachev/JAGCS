#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>

namespace domain
{
    class Vehicle: public QObject // TODO: system hierarchy
    {
        Q_OBJECT

        Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)

    public:
        enum Type
        {
            UnknownType = 0,
            FixedWingAircraft
        };

        explicit Vehicle(QObject* parent = nullptr);

        Type type() const;

    public slots:
        void setType(Type type);

    signals:
        void typeChanged(Type type);

    private:
        Type m_type;
    };
}

#endif // VEHICLE_H
