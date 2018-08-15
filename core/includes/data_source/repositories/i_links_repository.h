#ifndef I_LINKS_REPOSITORY_H
#define I_LINKS_REPOSITORY_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"

namespace data_source
{
    class ILinksRepository: public QObject
    {
        Q_OBJECT

    public:
        ILinksRepository(QObject* parent): QObject(parent) {}

        virtual dto::LinkDescriptionPtr description(int id) const = 0;
        virtual dto::LinkDescriptionPtrList descriptions() const = 0;

        virtual dto::LinkProtocolPtr protocol(int id) const = 0;
        virtual dto::LinkProtocolPtrList protocols() const = 0;

        virtual dto::LinkProtocolPtr protocolByName(const QString& name) const = 0;

    public slots:
        virtual bool save(const dto::LinkDescriptionPtr& description) = 0;
        virtual bool remove(const dto::LinkDescriptionPtr& description) = 0;

        virtual bool save(const dto::LinkProtocolPtr& protocol) = 0;
        virtual bool remove(const dto::LinkProtocolPtr& protocol) = 0;

    signals:
        void descriptionAdded(dto::LinkDescriptionPtr description);
        void descriptionRemoved(dto::LinkDescriptionPtr description);
        void descriptionChanged(dto::LinkDescriptionPtr description);

        void protocolAdded(dto::LinkProtocolPtr protocol);
        void protocolRemoved(dto::LinkProtocolPtr protocol);
        void protocolChanged(dto::LinkProtocolPtr protocol);
    };
}

#endif // I_LINKS_REPOSITORY_H
