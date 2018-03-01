#ifndef VIDEO_SETTINGS_PRESENTER_H
#define VIDEO_SETTINGS_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dao_traits.h"

namespace domain
{
    class VideoService;
}

namespace presentation
{
    class VideoSourceListPresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        explicit VideoSourceListPresenter(QObject* parent = nullptr);

    public slots:
        void updateVideoSources();
        void updateCameraInfo();

        void addDeviceVideo();
        void addStreamVideo();
        void setActiveVideo(int video);

    private:
        domain::VideoService* m_service;
    };
}

#endif // VIDEO_SETTINGS_PRESENTER_H
