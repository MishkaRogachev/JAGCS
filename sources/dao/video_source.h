#ifndef VIDEO_SOURCE_H
#define VIDEO_SOURCE_H

// Internal
#include "base_dao.h"

namespace dao
{
    class VideoSource: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(QString source READ source WRITE setSource)
        Q_PROPERTY(Type type READ type WRITE setType)

    public:
        enum Type: quint8
        {
            UnknownType = 0,
            Device,
            Stream
        };

        Type type() const;
        void setType(Type type);

        QString source() const;
        void setSource(const QString& source);

    private:
        Type m_type = UnknownType;
        QString m_source;

        Q_ENUM(Type)
    };
}

#endif // VIDEO_SOURCE_H
