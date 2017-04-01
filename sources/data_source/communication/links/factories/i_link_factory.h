#ifndef I_LINK_FACTORY_H
#define I_LINK_FACTORY_H

namespace data_source
{
    class AbstractLink;

    class ILinkFactory
    {
    public:
        ILinkFactory() {}
        virtual ~ILinkFactory() {}

        virtual AbstractLink* create() = 0;
    };
}

#endif // I_LINK_FACTORY_H
