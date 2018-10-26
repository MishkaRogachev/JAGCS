#ifndef I_LINK_FACTORY_H
#define I_LINK_FACTORY_H

#include <QSharedPointer>

namespace data_source
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

    using LinkFactoryPtr = QSharedPointer<ILinkFactory>;
}

#endif // I_LINK_FACTORY_H
