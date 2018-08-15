#include "database_presenter.h"

// Qt
#include <QVariant>
#include <QApplication>
#include <QDateTime>

// Internal
#include "settings_provider.h"
#include "db_manager.h"

using namespace presentation;

DatabasePresenter::DatabasePresenter(QObject* parent):
    BasePresenter(parent)
{}

void DatabasePresenter::updatePath()
{
    this->setViewProperty(PROPERTY(path), settings::Provider::value(settings::data_base::name));
    this->setViewProperty(PROPERTY(changed), false);
}

void DatabasePresenter::updateMigrations()
{
    this->setViewProperty(PROPERTY(migrations), dbManager->migrationVersions());
}

void DatabasePresenter::savePath()
{
    QString path = this->viewProperty(PROPERTY(path)).toString();

    if (settings::Provider::value(settings::data_base::name) == path)
    {
        this->setViewProperty(PROPERTY(changed), false);
        return;
    }

    settings::Provider::setValue(settings::data_base::name, path);

    qApp->exit(RESTART_CODE);

    // TODO: soft database reconnection
    //this->tryConnect();
    // this->setViewProperty(PROPERTY(changed), false);
}
