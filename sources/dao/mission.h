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
        enum Status: quint8 // TODO: move to assignment
        {
            NotActual = 0,
            Downloading,
            Uploading,
            Actual
        };

        QString name() const;
        void setName(const QString& name);

        int count() const;
        void setCount(int count);

        bool isVisible() const;
        void setVisible(bool visible);

        Status status() const;
        void setStatus(Status status);

    private:
        QString m_name;
        int m_count = 0;

        bool m_visible = true; // TODO: mission visibility to settings
        Status m_status = NotActual;

        Q_ENUM(Status)
    };
}

#endif // MISSION_H
