#include "video_source.h"

using namespace dto;

VideoSource::Type VideoSource::type() const
{
    return m_type;
}

void VideoSource::setType(VideoSource::Type type)
{
    m_type = type;
}

QString VideoSource::source() const
{
    return m_source;
}

void VideoSource::setSource(const QString& source)
{
    m_source = source;
}
