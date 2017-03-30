#include "communications_presenter.h"

using namespace presentation;

class CommunicationsPresenter::Impl
{
public:
};

CommunicationsPresenter::CommunicationsPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
}

CommunicationsPresenter::~CommunicationsPresenter()
{}

void CommunicationsPresenter::connectView(QObject* view)
{
}
