#ifndef DESCRIPTION_LINK_FACTORY_H
#define DESCRIPTION_LINK_FACTORY_H

// Internal
#include "i_link_factory.h"
#include "db_traits.h"

namespace comm
{
    class DescriptionLinkFactory: public ILinkFactory
    {
    public:
        DescriptionLinkFactory(const db::LinkDescriptionPtr& description =
                db::LinkDescriptionPtr());

        AbstractLink* create() override;
        void update(AbstractLink* link) override;

        db::LinkDescriptionPtr description() const;
        void setDescription(const db::LinkDescriptionPtr& description);

    private:
        db::LinkDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_LINK_FACTORY_H
