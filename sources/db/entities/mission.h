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
        Q_PROPERTY(int count READ count WRITE setCount)

    public:
        QString name() const;
        void setName(const QString& name);

        int count() const;
        void setCount(int count);

    private:
        QString m_name;
        int m_count = 0;
    };
}

#endif // MISSION_H
