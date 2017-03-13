#ifndef PERSISTABLE_H
#define PERSISTABLE_H

#include <QString>

namespace data_source
{
    class Persistable
    {
    public:
        Persistable();
        virtual ~Persistable();

        int id() const;

        bool createTable();
        bool dropTable();

        bool insert();

    protected:
        virtual const char* tableName() const = 0;
        virtual const char* tableParams() const = 0;
        virtual QString params() const = 0;

    private:
        class Impl;
        Impl* const d;

        Q_DISABLE_COPY(Persistable)
    };
}

#endif // PERSISTABLE_H
