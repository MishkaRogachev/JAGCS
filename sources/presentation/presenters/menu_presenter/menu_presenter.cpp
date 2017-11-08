#include "menu_presenter.h"

// Qt
#include <QDebug>

using namespace presentation;

class MenuPresenter::Impl
{
public:

};

MenuPresenter::MenuPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
}

MenuPresenter::~MenuPresenter()
{}

void MenuPresenter::connectView(QObject* view)
{

}

