#ifndef DESCRIPTION_LINK_FACTORY_H
#define DESCRIPTION_LINK_FACTORY_H

// Internal
#include "i_link_factory.h"
#include "dao_traits.h"

namespace comm
{
    class DescriptionLinkFactory: public ILinkFactory
    {
    public:
        DescriptionLinkFactory(const dao::LinkDescriptionPtr& description =
                dao::LinkDescriptionPtr());

        AbstractLink* create() override;
        void update(AbstractLink* link) override;

        dao::LinkDescriptionPtr description() const;
        void setDescription(const dao::LinkDescriptionPtr& description);

    private:
        dao::LinkDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_LINK_FACTORY_H
