#include "video_source_presenter.h"

// Qt
#include <QVariant>
#include <QDebug>

// Internal
#include "video_source.h"

#include "service_registry.h"
#include "video_service.h"

using namespace presentation;

VideoSourcePresenter::VideoSourcePresenter(QObject* parent):
    BasePresenter(parent),
    m_service(serviceRegistry->videoService())
{
    connect(m_service, &domain::VideoService::videoSourceChanged, this,
            [this](const dto::VideoSourcePtr& video) {
        if (video == m_video) this->updateSource();
    });
}

void VideoSourcePresenter::setVideo(int id)
{
    m_video = m_service->videoSource(id);

    this->updateSource();
}

void VideoSourcePresenter::updateSource()
{
    this->setViewProperty(PROPERTY(type), m_video ? m_video->type() : dto::VideoSource::UnknownType);
    this->setViewProperty(PROPERTY(source), m_video ? m_video->source() : "");

    this->setViewProperty(PROPERTY(changed), false);
}

void VideoSourcePresenter::setSource(const QString& source)
{
    if (m_video.isNull()) return;

    m_video->setSource(source);
    m_service->save(m_video);
}

void VideoSourcePresenter::remove()
{
    if (m_video) m_service->remove(m_video);
}

void VideoSourcePresenter::connectView(QObject* view)
{
    Q_UNUSED(view)

    this->updateSource();
}
