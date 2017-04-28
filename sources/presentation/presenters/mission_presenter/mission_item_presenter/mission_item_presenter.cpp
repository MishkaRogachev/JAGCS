#include "mission_item_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "domain_facade.h"

#include "mission_service.h"

#include "mission_item.h"

using namespace presentation;

class MissionItemPresenter::Impl
{
public:
    db::MissionItemPtr item;

};

MissionItemPresenter::MissionItemPresenter(domain::DomainFacade* facade,
                                           QObject* object):
    BasePresenter(object),
    d(new Impl())
{}

MissionItemPresenter::~MissionItemPresenter()
{}

void MissionItemPresenter::connectView(QObject* view)
{
    this->update();
}

void MissionItemPresenter::update()
{
    if (d->item)
    {
        this->setViewProperty(PROPERTY(command), d->item->command());
    }
    else
    {
        this->setViewProperty(PROPERTY(command), db::MissionItem::UnknownCommand);
    }
}
