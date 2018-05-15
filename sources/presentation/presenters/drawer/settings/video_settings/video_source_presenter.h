#ifndef VIDEO_SOURCE_PRESENTER_H
#define VIDEO_SOURCE_PRESENTER_H

// Internal
#include "base_presenter.h"
#include "dto_traits.h"

namespace domain
{
    class VideoService;
}

namespace presentation
{
    class VideoSourcePresenter: public BasePresenter
    {
        Q_OBJECT

    public:
        VideoSourcePresenter(QObject* parent = nullptr);

    public slots:
        void setVideo(int id);
        void updateView();
        void save();
        void remove();

    private:
        domain::VideoService* const m_service;
        dto::VideoSourcePtr m_video;
    };
}

#endif // VIDEO_SOURCE_PRESENTER_H
