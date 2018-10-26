#ifndef I_LINK_REPOSITORY_H
#define I_LINK_REPOSITORY_H

// Qt
#include "communication_link.h"

namespace domain
{
    class ILinkRepository: public QObject
    {
        Q_OBJECT

    public:
        explicit ILinkRepository(QObject* parent): QObject(parent) {}

        virtual LinkDescription* description(int id) const = 0;
        virtual QList<LinkDescription*> descriptions() const = 0;

    public slots:
        virtual bool save(LinkDescription* description) = 0;
        virtual bool remove(LinkDescription* description) = 0;

    signals:
        void descriptionAdded(LinkDescription* description);
        void descriptionRemoved(LinkDescription* description);
    };
}

#endif // I_LINK_REPOSITORY_H
