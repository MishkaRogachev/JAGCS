#ifndef VIDEO_PRESENTER_H
#define VIDEO_PRESENTER_H

#include "base_presenter.h"

class QAbstractVideoSurface;

namespace domain
{
    class SettingsProvider;
}

namespace presentation
{
    class VideoPresenter: public BasePresenter
    {
        Q_OBJECT

        Q_PROPERTY(QAbstractVideoSurface* videoSurface READ videoSurface
                   WRITE setVideoSurface)

    public:
        VideoPresenter(domain::SettingsProvider* settings, QObject* view);
        ~VideoPresenter() override;

        QAbstractVideoSurface* videoSurface() const;

    public slots:
        void setVideoSurface(QAbstractVideoSurface* videoSurface);
        void updateSource();

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // VIDEO_PRESENTER_H
