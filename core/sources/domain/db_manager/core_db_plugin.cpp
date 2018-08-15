#include "core_db_plugin.h"

// Internal
#include "init_migration.h"
#include "default_params_migration.h"

namespace
{
    QList<data_source::DbMigrationPtr> migrations =
    {
        QSharedPointer<data_source::InitMigration>::create(),
        QSharedPointer<data_source::DefaultParamsMigration>::create()
    };
}

using namespace domain;

CoreDbPlugin::CoreDbPlugin(QObject* parent):
    QObject(parent)
{}

QList<data_source::DbMigrationPtr> domain::CoreDbPlugin::migrations() const
{
    return ::migrations;
}
