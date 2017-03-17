#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

// Qt
#include <QObject>

class QSqlQuery;

namespace data_source
{
    class BaseEntity: public QObject
    {
        Q_OBJECT

    public:
        BaseEntity(int id, QObject* parent = nullptr);
        virtual ~BaseEntity();

        int id() const;

        virtual QList<QString> fields() const;

        virtual void bindQuery(QSqlQuery& query) const;
        virtual void updateFromQuery(const QSqlQuery& query);

    private:
        const int m_id;
    };
}

#endif // BASE_ENTITY_H
