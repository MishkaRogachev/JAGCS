#ifndef IDENTITY_TRAITS_H
#define IDENTITY_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace data_source
{
    class Mission;
    class MissionItem;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
}

#endif // IDENTITY_TRAITS_H
