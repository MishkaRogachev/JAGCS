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
    m_service(domain::ServiceRegistry::videoService())
{
    connect(m_service, &domain::VideoService::videoSourceChanged, this,
            [this](const dto::VideoSourcePtr& video) {
        if (video == m_video) this->updateView();
    });
}

void VideoSourcePresenter::setVideo(int id)
{
    m_video = m_service->videoSource(id);

    this->updateView();
}

void VideoSourcePresenter::updateView()
{
    this->setViewProperty(PROPERTY(type), m_video ? m_video->type() : dto::VideoSource::UnknownType);
    this->setViewProperty(PROPERTY(source), m_video ? m_video->source() : "");

    this->setViewProperty(PROPERTY(changed), false);
}

void VideoSourcePresenter::save()
{
    if (m_video.isNull()) return;

    m_video->setSource(this->viewProperty(PROPERTY(source)).toString());

    if (m_service->save(m_video)) this->setViewProperty(PROPERTY(changed), false);
}

void VideoSourcePresenter::remove()
{
    if (m_video) m_service->remove(m_video);
}
