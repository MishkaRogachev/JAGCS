#include "mission_presenter.h"

using namespace presentation;

class MissionPresenter::Impl
{
public:

};

MissionPresenter::MissionPresenter(QObject* object):
    BasePresenter(object),
    d(new Impl())
{}


MissionPresenter::~MissionPresenter()
{
    delete d;
}
