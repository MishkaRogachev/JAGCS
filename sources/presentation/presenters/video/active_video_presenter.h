#ifndef VIDEO_SPLIT_PRESENTER_H
#define VIDEO_SPLIT_PRESENTER_H

#include "video_presenter.h"

namespace presentation
{
    class ActiveVideoPresenter: public VideoPresenter
    {
        Q_OBJECT

    public:
        explicit ActiveVideoPresenter(QObject* parent = nullptr);

    public slots:
        void setActiveVideo(int videoId);
        void updateActiveVideo();
    };
}

#endif // VIDEO_SPLIT_PRESENTER_H
