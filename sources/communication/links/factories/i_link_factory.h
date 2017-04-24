#ifndef I_LINK_FACTORY_H
#define I_LINK_FACTORY_H

namespace comm
{
    class AbstractLink;

    class ILinkFactory
    {
    public:
        ILinkFactory() {}
        virtual ~ILinkFactory() {}

        virtual AbstractLink* create() = 0;
        virtual void update(AbstractLink* link) = 0;
    };
}

#endif // I_LINK_FACTORY_H
