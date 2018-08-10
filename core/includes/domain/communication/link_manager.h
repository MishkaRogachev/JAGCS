#ifndef LINK_MANAGER_H
#define LINK_MANAGER_H

// Qt
#include <QObject>

// Internal
#include "dto_traits.h"

namespace domain
{
    class LinkManager: public QObject
    {
        Q_OBJECT

    public:
        explicit LinkManager(QObject* parent = nullptr);
        ~LinkManager() override;

        dto::LinkDescriptionPtr description(int id) const;
        dto::LinkDescriptionPtrList descriptions() const;

        dto::LinkProtocolPtr protocol(int id) const;
        dto::LinkProtocolPtrList protocols() const;

    public slots:
        bool save(const dto::LinkDescriptionPtr& description);
        bool remove(const dto::LinkDescriptionPtr& description);

        bool save(const dto::LinkProtocolPtr& protocol);
        bool remove(const dto::LinkProtocolPtr& protocol);

    signals:
        void descriptionAdded(dto::LinkDescriptionPtr description);
        void descriptionRemoved(dto::LinkDescriptionPtr description);
        void descriptionChanged(dto::LinkDescriptionPtr description);

        void protocolAdded(dto::LinkProtocolPtr protocol);
        void protocolRemoved(dto::LinkProtocolPtr protocol);
        void protocolChanged(dto::LinkProtocolPtr protocol);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // LINK_MANAGER_H
