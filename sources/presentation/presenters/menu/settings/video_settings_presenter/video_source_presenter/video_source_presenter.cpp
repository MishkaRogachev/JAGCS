#include "video_source_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "video_service.h"
#include "video_source.h"

#include "video_presenter.h"

using namespace presentation;

VideoSourcePresenter::VideoSourcePresenter(domain::VideoService* service,
                                           const dao::VideoSourcePtr& video,
                                           QObject* parent):
    BasePresenter(parent),
    m_service(service),
    m_video(video),
    m_preview(nullptr)
{}

dao::VideoSourcePtr VideoSourcePresenter::video() const
{
    return m_video;
}

void VideoSourcePresenter::updateView()
{
    this->setViewProperty(PROPERTY(type), m_video->type());
    this->setViewProperty(PROPERTY(source), m_video->source());

    this->setViewProperty(PROPERTY(changed), false);
    if (m_preview) m_preview->updateSource();
}

void VideoSourcePresenter::save()
{
    m_video->setSource(this->viewProperty(PROPERTY(source)).toString());

    if (!m_service->save(m_video)) return;

    this->setViewProperty(PROPERTY(changed), false);
    if (m_preview) m_preview->updateSource();
}

void VideoSourcePresenter::remove()
{
    m_service->remove(m_video);
}

void VideoSourcePresenter::connectView(QObject* view)
{
    connect(view, SIGNAL(save()), this, SLOT(save()));
    connect(view, SIGNAL(restore()), this, SLOT(updateView()));
    connect(view, SIGNAL(remove()), this, SLOT(remove()));

    connect(view, SIGNAL(setupPreview(QObject*)), this, SLOT(setupPreview(QObject*)));

    this->updateView();
}

void VideoSourcePresenter::setupPreview(QObject* preview)
{
    if (!m_preview)
    {
        m_preview = new VideoPresenter(this);
        m_preview->setVideo(m_video);
        m_preview->setView(preview);
    }

    m_preview->setView(preview);
}
