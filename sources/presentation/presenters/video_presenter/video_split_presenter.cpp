#include "video_split_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "video_source.h"

#include "video_presenter.h"

using namespace presentation;

VideoSplitPresenter::VideoSplitPresenter(db::DbFacade* dbFacade, QObject* parent):
    BasePresenter(parent),
    m_dbFacade(dbFacade),
    m_video(new VideoPresenter(this))
{}

void VideoSplitPresenter::updateSources()
{
    QStringList videoSources;

    for (const db::VideoSourcePtr& videoSource: m_dbFacade->videoSources())
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
    m_video->setVideo(m_dbFacade->videoSources().at(index));
}
