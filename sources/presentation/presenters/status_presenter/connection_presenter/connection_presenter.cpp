#include "connection_presenter.h"

using namespace presentation;

class ConnectionPresenter::Impl
{
public:

};

ConnectionPresenter::ConnectionPresenter(QObject* view):
    BasePresenter(view),
    d(new Impl())
{}

ConnectionPresenter::~ConnectionPresenter()
{
    delete d;
}

void ConnectionPresenter::addSerialLink()
{

}

void ConnectionPresenter::addUdpLink()
{

}
