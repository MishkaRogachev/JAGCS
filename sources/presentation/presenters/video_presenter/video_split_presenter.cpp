#include "video_split_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "video_service.h"
#include "video_source.h"

#include "video_presenter.h"

using namespace presentation;

VideoSplitPresenter::VideoSplitPresenter(domain::VideoService* videoService, QObject* parent):
    BasePresenter(parent),
    m_videoService(videoService),
    m_video(new VideoPresenter(this))
{}

void VideoSplitPresenter::updateSources()
{
    QStringList videoSources;

    for (const dao::VideoSourcePtr& videoSource: m_videoService->videoSources())
    {
        videoSources.append(videoSource->source());
    }

    this->setViewProperty(PROPERTY(videoSources), QVariant::fromValue(videoSources));
}

void VideoSplitPresenter::connectView(QObject* view)
{
    m_video->setView(view);

    connect(view, SIGNAL(selectVideoSource(int)), this, SLOT(onSelectVideoSource(int)));

    this->updateSources();
}

void VideoSplitPresenter::onSelectVideoSource(int index)
{
    m_video->setVideo(m_videoService->videoSources().at(index));
}
