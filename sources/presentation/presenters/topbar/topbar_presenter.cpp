#include "topbar_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

class TopbarPresenter::Impl
{
public:
};

TopbarPresenter::TopbarPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
}

TopbarPresenter::~TopbarPresenter()
{}

