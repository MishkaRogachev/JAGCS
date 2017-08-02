#ifndef MISSION_H
#define MISSION_H

// Internal
#include "base_dao.h"

namespace dao
{
    class Mission: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(int count READ count WRITE setCount)

    public:
        QString name() const;
        void setName(const QString& name);

        int count() const;
        void setCount(int count);

        bool isVisible() const;
        void setVisible(bool visible);

    private:
        QString m_name;
        int m_count = 0;

        bool m_visible = true;
    };
}

#endif // MISSION_H
