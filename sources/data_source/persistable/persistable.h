#ifndef PERSISTABLE_H
#define PERSISTABLE_H

#include <QObject>

namespace data_source
{
    class Persistable: public QObject
    {
        Q_OBJECT

    public:
        explicit Persistable(QObject* parent = nullptr);

    };
}

#endif // PERSISTABLE_H
