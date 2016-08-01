#ifndef VIDEO_PRESENTER_H
#define VIDEO_PRESENTER_H

#include <QObject>

class QAbstractVideoSurface;

namespace presentation
{
    class VideoPresenter: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface
                   WRITE setVideoSurface)

    public:
        explicit VideoPresenter(QObject* parent = nullptr);
        ~VideoPresenter() override;

        QAbstractVideoSurface* videoSurface() const;

    public slots:
        void setVideoSurface(QAbstractVideoSurface* videoSurface);
        void updateSource();

    private:
        class Impl;
        Impl* const d;
        Q_DISABLE_COPY(VideoPresenter)
    };
}

#endif // VIDEO_PRESENTER_H
