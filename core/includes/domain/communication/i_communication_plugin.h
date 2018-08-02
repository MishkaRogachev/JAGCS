#ifndef I_COMMUNICATION_PLUIGN_H
#define I_COMMUNICATION_PLUIGN_H

#include <QObject>

namespace data_source
{
    class AbstractCommunicator;
}

namespace domain
{
    class ICommunicationPlugin
    {
        virtual data_source::AbstractCommunicator* createCommunicator() = 0;
    };
}

Q_DECLARE_INTERFACE(domain::ICommunicationPlugin, "domain.ICommunicationPlugin")

#endif // I_COMMUNICATION_PLUIGN_H
