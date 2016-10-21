#include "video_provider.h"

// Qt
#include <QAbstractVideoSurface>

using namespace presentation;

VideoProvider::VideoProvider(QObject* parent):
    QObject(parent),
    m_videoSurface(nullptr)
{}

QAbstractVideoSurface* VideoProvider::videoSurface() const
{
    return m_videoSurface;
}

void VideoProvider::setVideoSurface(QAbstractVideoSurface* videoSurface)
{
    if (m_videoSurface == videoSurface) return;
    m_videoSurface = videoSurface;

    emit videoSurfaceChanged(videoSurface);
}
