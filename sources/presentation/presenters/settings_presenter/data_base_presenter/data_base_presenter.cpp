#include "data_base_presenter.h"

// Qt
#include <QVariant>
#include <QDateTime>

// Internal
#include "settings_provider.h"

#include "domain_entry.h"
#include "db_manager.h"

using namespace presentation;

class DataBasePresenter::Impl
{
public:
    db::DbManager* manager;
};

DataBasePresenter::DataBasePresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->manager = entry->dbManager();
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
    this->setViewProperty(PROPERTY(migration), d->manager->migrationVersion());
    this->setViewProperty(PROPERTY(connected), d->manager->isOpen());
}

void DataBasePresenter::save()
{
    settings::Provider::setValue(settings::data_base::name,
                                 this->viewProperty(PROPERTY(path)));

    this->setViewProperty(PROPERTY(changed), false);
}

void DataBasePresenter::tryConnect()
{
    if (d->manager->isOpen()) d->manager->close();
    d->manager->open(settings::Provider::value(settings::data_base::name).toString());

    this->updateConnected();
}

void DataBasePresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(tryConnect()), this, SLOT(tryConnect()));

    this->updateView();
    this->updateConnected();
}
