#include "presenters_factory.h"

// Internal
#include "status_presenter.h"
#include "video_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(QObject* parent):
    QObject(parent)
{}

QObject* PresentersFactory::createStatusPresenter(QObject* parent)
{
    return new StatusPresenter(parent);
}

QObject* PresentersFactory::createVideoPresenter(QObject* parent)
{
    return new VideoPresenter(parent);
}
