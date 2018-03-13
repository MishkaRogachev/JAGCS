#include "database_presenter.h"

// Qt
#include <QVariant>
#include <QApplication>
#include <QDateTime>

// Internal
#include "common.h"
#include "settings_provider.h"

using namespace presentation;

DatabasePresenter::DatabasePresenter(QObject* parent):
    BasePresenter(parent)
{
    m_manager.clarify();

    connect(&m_manager, &db::DbManager::logChanged, this, &DatabasePresenter::updateLog);
}

void DatabasePresenter::updatePath()
{
    this->setViewProperty(PROPERTY(path), settings::Provider::value(settings::data_base::name));
    this->setViewProperty(PROPERTY(changed), false);
}

void DatabasePresenter::updateConnected()
{
    this->setViewProperty(PROPERTY(migration), m_manager.migrationVersion());
    this->setViewProperty(PROPERTY(connected), m_manager.isOpen());
}

void DatabasePresenter::updateLog()
{
    this->setViewProperty(PROPERTY(log), m_manager.dbLog());
}

void DatabasePresenter::clearLog()
{
    m_manager.clearLog();
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

    qApp->exit(RESETART_CODE);

    // TODO: soft database reconnection
    //this->tryConnect();
    // this->setViewProperty(PROPERTY(changed), false);
}

void DatabasePresenter::migrate()
{
    m_manager.migrateLastVersion();

    this->updateConnected();
}

void DatabasePresenter::tryConnect()
{
    if (m_manager.isOpen())
    {
        // FIXME: clear DB cache
        m_manager.close();
    }
    m_manager.open(settings::Provider::value(settings::data_base::name).toString());

    this->updateConnected();
}
