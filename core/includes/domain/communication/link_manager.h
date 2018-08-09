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
        void added(dto::LinkDescriptionPtr description);
        void removed(dto::LinkDescriptionPtr description);
        void changed(dto::LinkDescriptionPtr description);

        void added(dto::LinkProtocolPtr protocol);
        void removed(dto::LinkProtocolPtr protocol);
        void changed(dto::LinkProtocolPtr protocol);

    private:
        class Impl;
        QScopedPointer<Impl> const d;
    };
}

#endif // LINK_MANAGER_H
