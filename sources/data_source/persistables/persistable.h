#ifndef PERSISTABLE_H
#define PERSISTABLE_H

#include <QString>

namespace data_source
{
    class Persistable
    {
    public:
        Persistable();

        bool createTable();
        bool dropTable();

        //virtual bool save() = 0;

    protected:
        virtual QString tableName() const = 0;

        Q_DISABLE_COPY(Persistable)
    };
}

#endif // PERSISTABLE_H
