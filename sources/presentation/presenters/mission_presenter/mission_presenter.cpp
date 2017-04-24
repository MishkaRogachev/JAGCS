#include "mission_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:
    domain::DomainFacade* facade;
};

using namespace presentation;

MissionPresenter::MissionPresenter(domain::DomainFacade* facade,
                                   QObject* object):
    BasePresenter(object),
    d(new Impl())
{
    d->facade = facade;
}

MissionPresenter::~MissionPresenter()
{}

void MissionPresenter::connectView(QObject* view)
{

}
