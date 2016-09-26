#ifndef ABSTRACT_COMMUNICATOR_H
#define ABSTRACT_COMMUNICATOR_H

#include <QObject>

namespace domain
{
    class AbstractLink;
    class VehicleService;

    class AbstractCommunicator: public QObject
    {
        Q_OBJECT

    public:
        AbstractCommunicator(VehicleService* vehicleService, QObject* parent);

        virtual void receiveData(const QByteArray& data, AbstractLink* link) = 0;

    signals:
        void sendData(const QByteArray& data);

    protected:
        VehicleService* const m_vehicleService;
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
