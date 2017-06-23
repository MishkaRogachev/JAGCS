#include "command_presenter.h"

using namespace presentation;

class CommandPresenter::Impl
{
public:
    domain::CommandService* service = nullptr;
};

CommandPresenter::CommandPresenter(domain::CommandService* service, QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->service = service;
}

CommandPresenter::~CommandPresenter()
{}

void CommandPresenter::connectView(QObject* view)
{

}
