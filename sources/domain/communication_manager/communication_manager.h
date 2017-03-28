#ifndef COMMUNICATION_MANAGER_H
#define COMMUNICATION_MANAGER_H

#include <QObject>

namespace domain
{
    class ICommunicatorFactory;

    class CommunicationManager: public QObject
    {
        Q_OBJECT

    public:
        explicit CommunicationManager(ICommunicatorFactory* factory,
                                      QObject* parent = nullptr);
        ~CommunicationManager() override;

        void addUdpLonk();
        void addSerialLink();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // COMMUNICATION_MANAGER_H
