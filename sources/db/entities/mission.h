#ifndef MISSION_H
#define MISSION_H

// Internal
#include "base_entity.h"

namespace db
{
    class Mission: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)

    public:
        QString name() const;
        void setName(const QString& name);

    private:
        QString m_name;
    };
}

#endif // MISSION_H
