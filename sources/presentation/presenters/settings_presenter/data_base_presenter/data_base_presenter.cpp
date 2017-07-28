#include "data_base_presenter.h"

// Qt
#include <QVariant>
#include <QDateTime>

// Internal
#include "settings_provider.h"

#include "db_manager.h"

using namespace presentation;

class DataBasePresenter::Impl
{
public:
    db::DbManager manager;
};

DataBasePresenter::DataBasePresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{

    connect(&d->manager, &db::DbManager::logChanged, this, &DataBasePresenter::updateLog);
}

DataBasePresenter::~DataBasePresenter()
{}

void DataBasePresenter::updateView()
{
    this->setViewProperty(PROPERTY(path),
                          settings::Provider::value(settings::data_base::name));

    this->setViewProperty(PROPERTY(changed), false);
}

void DataBasePresenter::updateConnected()
{
    this->setViewProperty(PROPERTY(migration), d->manager.migrationVersion());
    this->setViewProperty(PROPERTY(connected), d->manager.isOpen());
}

void DataBasePresenter::updateLog()
{
    this->setViewProperty(PROPERTY(log), d->manager.dbLog());
}

void DataBasePresenter::clearLog()
{
    d->manager.clearLog();
}

void DataBasePresenter::save()
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

void DataBasePresenter::migrate()
{
    d->manager.migrateLastVersion();

    this->updateConnected();
}

void DataBasePresenter::tryConnect()
{
    if (d->manager.isOpen())
    {
        // FIXME: clear DB cache
        d->manager.close();
    }
    d->manager.open(settings::Provider::value(settings::data_base::name).toString());

    this->updateConnected();
}

void DataBasePresenter::connectView(QObject* view)
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
