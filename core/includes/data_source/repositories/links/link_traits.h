#ifndef LINK_TRAITS_H
#define LINK_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace dto
{
    class LinkDescription;
    using LinkDescriptionPtr = QSharedPointer<LinkDescription>;
    using LinkDescriptionPtrList = QList<LinkDescriptionPtr>;
}

Q_DECLARE_METATYPE(dto::LinkDescriptionPtr)

#endif // LINK_TRAITS_H
