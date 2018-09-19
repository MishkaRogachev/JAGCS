#ifndef I_LINK_REPOSITORY_H
#define I_LINK_REPOSITORY_H

// Qt
#include <QObject>

// Internal
#include "link_traits.h"

namespace data_source
{
    class ILinkRepository: public QObject
    {
        Q_OBJECT

    public:
        explicit ILinkRepository(QObject* parent): QObject(parent) {}

        virtual LinkDescriptionPtr description(int id) const = 0;
        virtual LinkDescriptionPtrList descriptions() const = 0;

    public slots:
        virtual bool save(const LinkDescriptionPtr& description) = 0;
        virtual bool remove(const LinkDescriptionPtr& description) = 0;

    signals:
        void descriptionAdded(LinkDescriptionPtr description);
        void descriptionRemoved(LinkDescriptionPtr description);
        void descriptionChanged(LinkDescriptionPtr description);
    };
}

#endif // I_LINK_REPOSITORY_H
