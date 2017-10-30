#include "unified_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "topbar_presenter.h"

using namespace presentation;

class UnifiedPresenter::Impl
{
public:
    TopbarPresenter* topbar;
};

UnifiedPresenter::UnifiedPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->topbar = new TopbarPresenter(this);
}

UnifiedPresenter::~UnifiedPresenter()
{}

void UnifiedPresenter::connectView(QObject* view)
{
    d->topbar->setView(view->findChild<QObject*>(NAME(topbar)));
}
