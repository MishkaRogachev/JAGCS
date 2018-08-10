#ifndef CORE_DB_PLUGIN_H
#define CORE_DB_PLUGIN_H

// Qt
#include <QObject>

// Internal
#include "i_db_plugin.h"

namespace domain
{
    class CoreDbPlugin: public QObject, public IDbPlugin
    {
        Q_OBJECT

    public:
        explicit CoreDbPlugin(QObject* parent = nullptr);

        QList<data_source::DbMigrationPtr> migrations() const override;
    };
}

#endif // CORE_DB_PLUGIN_H
