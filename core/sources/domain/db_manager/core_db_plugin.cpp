#include "core_db_plugin.h"

// Internal
#include "init_migration.h"
#include "default_params_migration.h"

using namespace domain;

CoreDbPlugin::CoreDbPlugin(QObject* parent):
    QObject(parent)
{}

QList<data_source::DbMigrationPtr> domain::CoreDbPlugin::migrations() const
{
    QList<data_source::DbMigrationPtr> list;

    list.append(QSharedPointer<data_source::InitMigration>::create());
    list.append(QSharedPointer<data_source::DefaultParamsMigration>::create());

    return list;
}
