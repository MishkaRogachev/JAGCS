#ifndef DESCRIPTION_LINK_FACTORY_H
#define DESCRIPTION_LINK_FACTORY_H

// Internal
#include "i_link_factory.h"
#include "db_traits.h"

namespace data_source
{
    class DescriptionLinkFactory: public ILinkFactory
    {
    public:
        DescriptionLinkFactory(
                const LinkDescriptionPtr& description = LinkDescriptionPtr());

        AbstractLink* create() override;

        LinkDescriptionPtr description() const;
        void setDescription(const LinkDescriptionPtr& description);

    private:
        LinkDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_LINK_FACTORY_H
