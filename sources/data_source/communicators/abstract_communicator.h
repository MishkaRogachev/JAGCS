#ifndef ABSTRACT_COMMUNICATOR_H
#define ABSTRACT_COMMUNICATOR_H

#include <QObject>

namespace data_source
{
    class AbstractLink;
    class AbstractCommunicator: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractCommunicator(QObject* parent = nullptr);

        virtual void receiveData(const QByteArray& data, AbstractLink* link) = 0;

    signals:
        void sendData(const QByteArray& data);
    };
}

#endif // ABSTRACT_COMMUNICATOR_H
