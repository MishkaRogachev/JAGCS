#ifndef I_DB_PROVIDER_H
#define I_DB_PROVIDER_H

// Qt
class QSqlDatabase;

namespace data_source
{
    class IDbProvider
    {
    public:
        virtual ~IDbProvider() {}

        virtual QSqlDatabase& database() = 0;
        virtual bool open(bool& exists) = 0;
    };
}

#endif // I_DB_PROVIDER_H

