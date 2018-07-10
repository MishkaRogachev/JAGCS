#ifndef I_COMMUNICATOR_FACTORY_H
#define I_COMMUNICATOR_FACTORY_H

#include <QtGlobal>

namespace data_source
{
    class AbstractCommunicator;

    class ICommunicatorFactory
    {
    public:
        ICommunicatorFactory() {}
        virtual ~ICommunicatorFactory() {}

        virtual AbstractCommunicator* create() = 0;
    };
}

#endif // I_COMMUNICATOR_FACTORY_H
