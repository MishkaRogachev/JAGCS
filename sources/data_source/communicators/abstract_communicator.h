#ifndef ABSTRACTCOMMUNICATOR_H
#define ABSTRACTCOMMUNICATOR_H

#include <QtCore/QObject>

namespace data_source
{
    class AbstractCommunicator: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractCommunicator(QObject* parent = nullptr);

    public slots:
        virtual void receiveData(const QByteArray& data) = 0;

    signals:
        void sendData(const QByteArray& data);
    };
}

#endif // ABSTRACTCOMMUNICATOR_H
