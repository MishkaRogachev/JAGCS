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

void DatabasePresenter::updateConnected()
{
    //this->setViewProperty(PROPERTY(migration), dbManager->migrationVersion());
    this->setViewProperty(PROPERTY(connected), dbManager->isOpen());
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

void DatabasePresenter::migrate()
{
    dbManager->checkMissing();

    this->updateConnected();
}

void DatabasePresenter::tryConnect()
{
    if (dbManager->isOpen())
    {
        // FIXME: clear DB cache
        dbManager->closeConnection();
    }
    dbManager->open(settings::Provider::value(settings::data_base::name).toString());

    this->updateConnected();
}
