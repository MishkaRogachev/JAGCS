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

        virtual dto::LinkDescriptionPtr description(int id) const = 0;
        virtual dto::LinkDescriptionPtrList descriptions() const = 0;

    public slots:
        virtual bool save(const dto::LinkDescriptionPtr& description) = 0;
        virtual bool remove(const dto::LinkDescriptionPtr& description) = 0;

    signals:
        void descriptionAdded(dto::LinkDescriptionPtr description);
        void descriptionRemoved(dto::LinkDescriptionPtr description);
        void descriptionChanged(dto::LinkDescriptionPtr description);
    };
}

#endif // I_LINK_REPOSITORY_H
