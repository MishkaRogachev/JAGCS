#ifndef LINK_PROTOCOL_H
#define LINK_PROTOCOL_H

// Internal
#include "base_dto.h"

// Qt
#include <QVariant>
#include <QMap>

namespace dto
{
    class LinkProtocol: public BaseDto
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(QString description READ description WRITE setDescription)

    public:
        QString name() const;
        void setName(const QString& name);

        QString description() const;
        void setDescription(const QString& description);

    private:
        QString m_name;
        QString m_description;
    };
}

#endif // LINK_PROTOCOL_H
