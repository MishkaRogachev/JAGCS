#ifndef I_COMMUNICATOR_FACTORY_H
#define I_COMMUNICATOR_FACTORY_H

namespace data_source
{
    class AbstractCommunicator;
}

namespace domain
{
    class ICommunicatorFactory
    {
    public:
        ICommunicatorFactory() {}
        virtual ~ICommunicatorFactory() {}

        virtual data_source::AbstractCommunicator* create() = 0;
    };
}

#endif // I_COMMUNICATOR_FACTORY_H
