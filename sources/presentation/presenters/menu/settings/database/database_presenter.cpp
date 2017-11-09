#include "database_presenter.h"

// Qt
#include <QVariant>
#include <QDateTime>

// Internal
#include "settings_provider.h"

#include "db_manager.h"

using namespace presentation;

class DatabasePresenter::Impl
{
public:
    db::DbManager manager;
};

DatabasePresenter::DatabasePresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->manager.clarify();

    connect(&d->manager, &db::DbManager::logChanged, this, &DatabasePresenter::updateLog);
}

DatabasePresenter::~DatabasePresenter()
{}

void DatabasePresenter::updateView()
{
    this->setViewProperty(PROPERTY(path),
                          settings::Provider::value(settings::data_base::name));

    this->setViewProperty(PROPERTY(changed), false);
}

void DatabasePresenter::updateConnected()
{
    this->setViewProperty(PROPERTY(migration), d->manager.migrationVersion());
    this->setViewProperty(PROPERTY(connected), d->manager.isOpen());
}

void DatabasePresenter::updateLog()
{
    this->setViewProperty(PROPERTY(log), d->manager.dbLog());
}

void DatabasePresenter::clearLog()
{
    d->manager.clearLog();
}

void DatabasePresenter::save()
{
    if (settings::Provider::value(settings::data_base::name) !=
        this->viewProperty(PROPERTY(path)))
    {
        settings::Provider::setValue(settings::data_base::name,
                                     this->viewProperty(PROPERTY(path)));
        this->tryConnect();
    }

    this->setViewProperty(PROPERTY(changed), false);
}

void DatabasePresenter::migrate()
{
    d->manager.migrateLastVersion();

    this->updateConnected();
}

void DatabasePresenter::tryConnect()
{
    if (d->manager.isOpen())
    {
        // FIXME: clear DB cache
        d->manager.close();
    }
    d->manager.open(settings::Provider::value(settings::data_base::name).toString());

    this->updateConnected();
}

void DatabasePresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(clearLog()), this, SLOT(clearLog()));
    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(tryConnect()), this, SLOT(tryConnect()));
    connect(view, SIGNAL(migrate()), this, SLOT(migrate()));

    this->updateView();
    this->updateConnected();
    this->updateLog();
}
