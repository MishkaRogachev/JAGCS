#ifndef DESCRIPTION_LINK_FACTORY_H
#define DESCRIPTION_LINK_FACTORY_H

// Internal
#include "i_link_factory.h"
#include "dto_traits.h"

namespace data_source
{
    class DescriptionLinkFactory: public ILinkFactory
    {
    public:
        DescriptionLinkFactory(const dto::LinkDescriptionPtr& description);

        AbstractLink* create() override;
        void update(AbstractLink* link) override;

        dto::LinkDescriptionPtr description() const;
        void setDescription(const dto::LinkDescriptionPtr& description);

    private:
        dto::LinkDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_LINK_FACTORY_H
