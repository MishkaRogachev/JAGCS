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
        DescriptionLinkFactory(const data_source::LinkDescriptionPtr& description =
                data_source::LinkDescriptionPtr());

        AbstractLink* create() override;
        void update(AbstractLink* link) override;

        data_source::LinkDescriptionPtr description() const;
        void setDescription(const data_source::LinkDescriptionPtr& description);

    private:
        data_source::LinkDescriptionPtr m_description;
    };
}

#endif // DESCRIPTION_LINK_FACTORY_H
