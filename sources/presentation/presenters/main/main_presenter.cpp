#include "main_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "topbar_presenter.h"
#include "menu_presenter.h"

using namespace presentation;

class MainPresenter::Impl
{
public:
    TopbarPresenter* topbar;
    MenuPresenter* menu;
};

MainPresenter::MainPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->topbar = new TopbarPresenter(this);
    d->menu = new MenuPresenter(this);
}

MainPresenter::~MainPresenter()
{}

void MainPresenter::connectView(QObject* view)
{
    d->topbar->setView(view->findChild<QObject*>(NAME(topbar)));
    d->menu->setView(view->findChild<QObject*>(NAME(menu)));
}
