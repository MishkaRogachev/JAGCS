#include "main_presenter.h"

// Qt
#include <QDebug>

// Internal
#include "topbar_presenter.h"
#include "location_map_presenter.h"
#include "video_split_presenter.h"
#include "menu_presenter.h"

using namespace presentation;

class MainPresenter::Impl
{
public:
    TopbarPresenter* topbar;
    LocationMapPresenter* map;
    VideoSplitPresenter* video;
    MenuPresenter* menu;
};

MainPresenter::MainPresenter(QObject* parent):
    BasePresenter(parent),
    d(new Impl())
{
    d->topbar = new TopbarPresenter(this);
    d->map = new  LocationMapPresenter(this);
    d->video = new VideoSplitPresenter(this);
    d->menu = new MenuPresenter(this);
}

MainPresenter::~MainPresenter()
{}

void MainPresenter::connectView(QObject* view)
{
    d->topbar->setView(view->findChild<QObject*>(NAME(topbar)));
    d->menu->setView(view->findChild<QObject*>(NAME(menu)));
    d->map->setView(view->findChild<QObject*>(NAME(map)));
    d->video->setView(view->findChild<QObject*>(NAME(video)));
}
