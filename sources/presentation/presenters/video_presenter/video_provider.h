#ifndef VIDEO_PROVIDER_H
#define VIDEO_PROVIDER_H

#include <QObject>

class QAbstractVideoSurface;

namespace presentation
{
    class VideoProvider: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface
                   WRITE setVideoSurface NOTIFY videoSurfaceChanged)

    public:
        explicit VideoProvider(QObject* parent = nullptr);

        QAbstractVideoSurface* videoSurface() const;

    public slots:
        void setVideoSurface(QAbstractVideoSurface* videoSurface);

    signals:
        void videoSurfaceChanged(QAbstractVideoSurface* videoSurface);

    private:
        QAbstractVideoSurface* m_videoSurface;
    };
}

#endif // VIDEO_PROVIDER_H
