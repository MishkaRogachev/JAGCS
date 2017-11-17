#include "presenters_factory.h"

// Internal
#include "topbar_presenter.h"
#include "location_map_presenter.h"
#include "active_video_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(QObject* parent):
    QObject(parent)
{}

QObject* PresentersFactory::createTopbarPresenter(QObject* view)
{
    TopbarPresenter* topBar = new TopbarPresenter(view);
    topBar->setView(view);
    return topBar;
}

QObject* PresentersFactory::createMapPresenter(QObject* view)
{
    AbstractMapPresenter* map = new LocationMapPresenter(view);
    map->setView(view);
    return map;
}

QObject* PresentersFactory::createVideoPresenter(QObject* view)
{
    VideoPresenter* video = new ActiveVideoPresenter(view);
    video->setView(view);
    return video;
}
