#include "data_base_presenter.h"

// Internal
#include "settings_provider.h"

using namespace presentation;

class DataBasePresenter::Impl
{
public:

};

DataBasePresenter::DataBasePresenter(domain::DomainEntry* entry, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{}

DataBasePresenter::~DataBasePresenter()
{}

void DataBasePresenter::updateView()
{
    this->setViewProperty(PROPERTY(path),
                          settings::Provider::value(settings::data_base::name));

    this->setViewProperty(PROPERTY(changed), false);
}

void DataBasePresenter::save()
{
    settings::Provider::setValue(settings::data_base::name,
                                 this->viewProperty(PROPERTY(path)));

    this->setViewProperty(PROPERTY(changed), false);
}

void DataBasePresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));

    this->updateView();
}
