#include "default_params_migration.h"

// Qt
#include <QCoreApplication>
#include <QDebug>

// Internal
#include "settings_provider.h"

using namespace data_source;

bool DefaultParamsMigration::upImpl()
{
    if (!m_query.prepare(QString("INSERT INTO vehicles (mavId, name, type) "
                                 "VALUES (1, \'%1\', 1)").arg(
                             qApp->translate("DefaultParamsMigration", "MAV 1")))
        || !m_query.exec()) return false;

    settings::Provider::setValue(settings::vehicle::vehicle + QString::number(1) +
                                 "/" + settings::vehicle::instruments::status +
                                 "/" + settings::visibility, true);
    settings::Provider::setValue(settings::vehicle::vehicle + QString::number(1) +
                                 "/" + settings::vehicle::instruments::fd +
                                 "/" + settings::visibility, true);
    settings::Provider::setValue(settings::vehicle::vehicle + QString::number(1) +
                                 "/" + settings::vehicle::instruments::hsi +
                                 "/" + settings::visibility, true);

    return AbstractMigration::upImpl();
}

bool DefaultParamsMigration::downImpl()
{
    // No need to drop default values

    return true;
}

QString DefaultParamsMigration::version() const
{
    return "core_2018.08.07-09:38_default_params";
}
