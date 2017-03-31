#include "communication_link_presenter.h"

using namespace presentation;

class CommunicationLinkPresenter::Impl
{
public:
};

CommunicationLinkPresenter::CommunicationLinkPresenter(
        QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
}

CommunicationLinkPresenter::~CommunicationLinkPresenter()
{}

void CommunicationLinkPresenter::connectView(QObject* view)
{
}
