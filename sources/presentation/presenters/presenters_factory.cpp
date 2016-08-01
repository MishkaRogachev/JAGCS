#include "presenters_factory.h"

// Internal
#include "video_presenter.h"

using namespace presentation;

PresentersFactory::PresentersFactory(QObject* parent):
    QObject(parent)
{}

QObject* PresentersFactory::createVideoPresenter(QObject* parent)
{
    return new VideoPresenter(parent);
}
