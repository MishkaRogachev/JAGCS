#include "video_source_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "db_facade.h"
#include "video_source.h"

#include "video_presenter.h"

using namespace presentation;

VideoSourcePresenter::VideoSourcePresenter(db::DbFacade* facade,
                                           const db::VideoSourcePtr& video,
                                           QObject* parent):
    BasePresenter(parent),
    m_facade(facade),
    m_video(video),
    m_preview(nullptr)
{}

db::VideoSourcePtr VideoSourcePresenter::video() const
{
    return m_video;
}

void VideoSourcePresenter::restore()
{
    this->setViewProperty(PROPERTY(type), m_video->type());
    this->setViewProperty(PROPERTY(source), m_video->source());

    this->setViewProperty(PROPERTY(changed), false);
    if (m_preview) m_preview->updateSource();
}

void VideoSourcePresenter::save()
{
    m_video->setSource(this->viewProperty(PROPERTY(source)).toString());

    if (!m_facade->save(m_video)) return;

    this->setViewProperty(PROPERTY(changed), false);
    if (m_preview) m_preview->updateSource();
}

void VideoSourcePresenter::remove()
{
    m_facade->remove(m_video);
}

void VideoSourcePresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(restore()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    connect(view, SIGNAL(setupPreview(QObject*)), this, SLOT(setupPreview(QObject*)));

    this->restore();
}

void VideoSourcePresenter::setupPreview(QObject* preview)
{
    if (!m_preview) m_preview = new VideoPresenter(m_video, this);
    m_preview->setView(preview);
}
